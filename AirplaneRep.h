#pragma once
class AirplaneRep
{
private:
	struct Airplane {
		unsigned long miles;
		char type;
	};
private:
	union 
	{
		Airplane rep;
		AirplaneRep* next;
	};
public:
	unsigned long getMiles() { return rep.miles; }
	char getType() { return rep.type; }

	void set(unsigned long m, char t) {
		rep.miles = m;
		rep.type = t;
	}
public:
	static void* operator new (size_t size);
	static void operator delete(void* deafObject, size_t size);
private:
	static const int BLOCK_SIZE;
	static AirplaneRep* headOfFreeList;
};


