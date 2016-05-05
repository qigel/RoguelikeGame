#include "main.hpp"

Engine::Engine(int screenWidth, int screenHeight) : gameStatus(STARTUP), fovRadius(15), screenWidth(screenWidth), screenHeight(screenHeight)
{
	TCODConsole::setCustomFont("MainFont.bmp", TCOD_FONT_LAYOUT_ASCII_INROW | TCOD_FONT_TYPE_GREYSCALE, 16, 32);
	TCODConsole::initRoot(screenWidth, screenHeight, "Test window", false);
	TCODMouse::showCursor(true);
	player = new Actor(0, 0, 256, "Игрок");
	player->destructible = new PlayerDestructible(1000, 2, "Твои останки"); //heal and armor
	player->attacker = new Attacker(5); //power
	player->ai = new PlayerAi();
	player->container = new Container(26); //size of the inventory
	actors.push(player);
	map = new Map(100, 100); //widht and height
	gui = new Gui();
	gui->message(TCODColor::darkerYellow, "Приветствую тебя, о великий Тестер!\nПриготовься насладиться незабываемой игрой.");
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
	map->render(player->x - screenWidth / 2, player->y - screenHeight / 2, screenWidth, screenHeight);
	// draw the actors
	for (Actor **iterator = actors.begin();
		iterator != actors.end(); iterator++) 
	{
		Actor *actor = *iterator;
		if (map->isInFov(actor->x, actor->y))
		{
			actor->render(-player->x + screenWidth / 2, -player->y + screenHeight / 2);
		}
	}
	player->render(-player->x + screenWidth / 2, -player->y + screenHeight / 2);
	// show the player's stats
	gui->render(player->x - screenWidth / 2, player->y - screenHeight / 2);
	TCODConsole::root->print(0, screenHeight - 1, "Жми 'Esc' чтобы выйти");
	TCODConsole::root->print(0, screenHeight - 2, "X=%d Y=%d",player->x, player->y);
	TCODConsole::root->print(0, screenHeight - 3, "mX=%d mY=%d", mouse.cx + player->x - screenWidth / 2, mouse.cy + player->y - screenHeight / 2);
}

void Engine::sendToBack(Actor *actor)
{
	actors.remove(actor);
	actors.insertBefore(actor, 0);
}