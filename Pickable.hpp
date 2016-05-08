

class Pickable  : public Persistent
{
public:
	bool pick(Actor *owner, Actor *wearer);
	virtual bool use(Actor *owner, Actor *wearer);
	virtual ~Pickable() {};
	static Pickable *create(TCODZip &zip);
protected:
	enum PickableType {
		HEALER
	};
};

class Healer : public Pickable
{
public:
	float amount; // how many hp

	Healer(float amount);
	bool use(Actor *owner, Actor *wearer);
	void load(TCODZip &zip);
	void save(TCODZip &zip);
};