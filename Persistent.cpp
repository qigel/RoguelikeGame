#include "main.hpp"
void Engine::save() {
	if (player->destructible->isDead()) {
		TCODSystem::deleteFile("game.sav");
	}
	else {
		TCODZip zip;
		// save the map first
		zip.putInt(map->width);
		zip.putInt(map->height);
		map->save(zip);
		// then the player
		player->save(zip);
		// then the stairs
		stairs->save(zip);
		// then all the other actors
		zip.putInt(actors.size() - 2);
		for (Actor **it = actors.begin(); it != actors.end(); it++) 
		{
			if (*it != player && *it != stairs) 
			{
				(*it)->save(zip);
			}
		}
		gui->save(zip);
		zip.saveToFile("game.sav");
	}
}

void Engine::load()
{
	if (TCODSystem::fileExists("game.sav"))
	{
		engine.gui->menu.clear();
		engine.gui->menu.addItem(Menu::NEW_GAME, "Новая игра");
		if (TCODSystem::fileExists("game.sav")) 
		{
			engine.gui->menu.addItem(Menu::CONTINUE, "Продолжить");
		}
		engine.gui->menu.addItem(Menu::EXIT, "Выход");
		Menu::MenuItemCode menuItem = engine.gui->menu.pick();
		if (menuItem == Menu::EXIT || menuItem == Menu::NONE)
		{
			// Exit or window closed
			exit(0);
		}
		else if (menuItem == Menu::NEW_GAME)
		{
			// New game
			engine.term();
			engine.init();
		}
		else {
			TCODZip zip;
			// continue a saved game
			engine.term();
			zip.loadFromFile("game.sav");
			// load the map
			int width = zip.getInt();
			int height = zip.getInt();
			map = new Map(width, height);
			map->load(zip);
			// then the player
			player = new Actor(0, 0, 10, NULL);
			player->load(zip);
			actors.push(player);
			// the stairs
			stairs = new Actor(0, 0, 0, NULL);
			stairs->load(zip);
			actors.push(stairs);
			// then all other actors
			int nbActors = zip.getInt();
			while (nbActors > 0)
			{
				Actor *actor = new Actor(0, 0, 10, NULL);
				actor->load(zip);
				actors.push(actor);
				nbActors--;
			}
			// finally the message log
			gui->load(zip);
			// to force FOV recomputation
			gameStatus = STARTUP;
		}
	}
}