class Engine
{
public:
	int screenWidth;
	int screenHeight;
	Gui *gui;
	Engine(int screenWidth, int screenHeight);
	TCOD_key_t lastKey;
	TCOD_mouse_t mouse;
	TCODList<Actor *> actors;
	enum GameStatus
	{
		STARTUP,
		IDLE,
		NEW_TURN,
		VICTORY,
		DEFEAT
	} gameStatus;
	Actor *player;
	Map *map;
	int fovRadius;
	~Engine();
	void update();
	void render();
	void sendToBack(Actor *actor);
private:
	bool computeFov;
};

extern Engine engine;