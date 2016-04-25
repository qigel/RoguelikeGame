class Engine
{
public:
	int screenWidth;
	int screenHeight;
	TCOD_key_t lastKey;
	Engine(int screenWidth, int screenHeight);
	enum GameStatus
	{
		STARTUP,
		IDLE,
		NEW_TURN,
		VICTORY,
		DEFEAT
	} gameStatus;
	TCODList<Actor *> actors;
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