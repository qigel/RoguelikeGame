class Ai : public Persistent
{
public:
	virtual void update(Actor *owner) = 0;
	static Ai *create(TCODZip &zip);
protected:
	enum AiType
	{
		MONSTER, PLAYER
	};
};

class MonsterAi : public Ai
{
public:
	MonsterAi();
	void update(Actor *owner);
	void load(TCODZip &zip);
	void save(TCODZip &zip);
protected:
	int moveCount;
	void moveOrAttack(Actor *owner, int targetx, int targety);
};

class PlayerAi : public Ai 
{
public:
	int xpLevel;
	PlayerAi();
	int getNextLevelXp();
	void update(Actor *owner);
	void load(TCODZip &zip);
	void save(TCODZip &zip);
protected:
	bool moveOrAttack(Actor *owner, int targetx, int targety);
	void handleActionKey(Actor *owner, int ascii);
	Actor *choseFromInventory(Actor *owner);
};