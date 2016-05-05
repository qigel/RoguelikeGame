class Ai 
{
public:
	virtual void update(Actor *owner) = 0;
	virtual ~Ai() {};
};

class PlayerAi : public Ai
{
public:
	void handleActionKey(Actor *owner, int ascii);
	void update(Actor *owner);
protected:
	bool moveOrAttack(Actor *owner, int targetx, int targety);
	Actor *choseFromInventory(Actor *owner);
};

class MonsterAi : public Ai
{
public:
	MonsterAi();
	void update(Actor *owner);

protected:
	int moveCount;
	void moveOrAttack(Actor *owner, int targetx, int targety);
};

