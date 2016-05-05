#include "main.hpp"

Engine::Engine(int screenWidth, int screenHeight) : gameStatus(STARTUP), fovRadius(15), screenWidth(screenWidth), screenHeight(screenHeight)
{
	TCODConsole::setCustomFont("newplot.png", TCOD_FONT_LAYOUT_ASCII_INROW | TCOD_FONT_TYPE_GREYSCALE, 16, 18);
	TCODConsole::initRoot(screenWidth, screenHeight, "Test window", false);
	player = new Actor(0, 0, 256, "Игрок");
	player->destructible = new PlayerDestructible(30, 2, "Твои останки");
	player->attacker = new Attacker(5);
	player->ai = new PlayerAi();
	actors.push(player);
	map = new Map(80, 36);
	gui = new Gui();
	gui->message(TCODColor::red, "Приветствую тебя, о великий Тестер!\nПриготовься насладиться незабываемой игрой.");
}

Engine::~Engine() 
{
	actors.clearAndDelete();
	delete map;
	delete gui;
}

void Engine::update()
{
	if (gameStatus == STARTUP) map->computeFov();
	gameStatus = IDLE;
	TCODSystem::checkForEvent(TCOD_EVENT_KEY_PRESS | TCOD_EVENT_MOUSE, &lastKey, &mouse);
	player->update();
	if (gameStatus == NEW_TURN)
	{
		for (Actor **iterator = actors.begin(); iterator != actors.end();
			iterator++) {
			Actor *actor = *iterator;
			if (actor != player) {
				actor->update();
			}
		}
	}
	switch (engine.lastKey.vk)
	{
		case TCODK_ESCAPE: exit(0); break;
		default:break;
	}
}

void Engine::render() 
{
	TCODConsole::root->clear();
	// draw the map
	map->render();
	// draw the actors
	for (Actor **iterator = actors.begin();
		iterator != actors.end(); iterator++) 
	{
		Actor *actor = *iterator;
		if (map->isInFov(actor->x, actor->y))
		{
			actor->render();
		}
	}
	player->render();
	// show the player's stats
	gui->render();
	TCODConsole::root->print(0, screenHeight - 1, "Жми 'Esc' чтобы выйти");
}

void Engine::sendToBack(Actor *actor)
{
	actors.remove(actor);
	actors.insertBefore(actor, 0);
}