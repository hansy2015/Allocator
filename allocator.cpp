#include "allocator.h"

void* allocator::allocate(size_t size)
{
	obj* p;
	if (!freeStore)
	{
		size_t chunk = CHUNK * size;
		freeStore = p = static_cast<obj*>(new obj[chunk]);
		for (int i = 0; i < CHUNK - 1; i++) {
			p->next = p + 1;
			p = p->next;
		}
		p->next = nullptr;

	}
	p = freeStore;
	freeStore = freeStore->next;
	return p;
}