#pragma once
class allocator
{
private:
	struct obj {
		struct obj* next;
	};
public:
	void* allocate(size_t);
	void deallocate(void*, size_t);
private:
	obj* freeStore = nullptr;
	const int CHUNK = 5;
};



