#include "AirplaneRep.h"
AirplaneRep* AirplaneRep::headOfFreeList;
const int AirplaneRep::BLOCK_SIZE = 512;

void* AirplaneRep::operator new(size_t size)
{
	AirplaneRep* p = headOfFreeList;
	if (p) {
		headOfFreeList = p->next;
	}
	else {
		AirplaneRep* newBlock = static_cast<AirplaneRep*>(new AirplaneRep[BLOCK_SIZE]);
		for (int i = 1; i < BLOCK_SIZE - 1; i++) {
			newBlock[i].next = &newBlock[i + 1];
		}
		newBlock[BLOCK_SIZE - 1].next = 0;
		p = newBlock;
		headOfFreeList = &newBlock[1];
	}
	return p;
}

void AirplaneRep::operator delete(void* deadObject, size_t szie) {
	AirplaneRep* carcass = static_cast<AirplaneRep*>(deadObject);
	carcass->next = headOfFreeList;
	headOfFreeList = carcass;
}