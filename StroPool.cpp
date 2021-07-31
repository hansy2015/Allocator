// StroPool.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include <iostream>
#include "AirplaneRep.h"

using namespace std;

class Screen {
public:
    Screen(int x) : i(x) {}
    int get() { return i; }
    void* operator new (size_t);
    void operator delete(void*, size_t);
private:
    Screen* next;
    static Screen* freeStore;
    static const int screenChunk;
private:
    int i;
};

Screen* Screen::freeStore = 0;
const int Screen::screenChunk = 24;

void* Screen::operator new(size_t size) {
    Screen* p;
    if (!freeStore) {
        size_t chunk = screenChunk * size;
        freeStore = p = reinterpret_cast<Screen*>(new char[chunk]);
        for (; p != &freeStore[screenChunk - 1]; ++p)
            p->next = p + 1;

        p->next = 0;
    }
    p = freeStore;
    freeStore = freeStore->next;
    return p;
}

void Screen::operator delete(void* p, size_t) {
    static_cast<Screen*>(p)->next = freeStore;
    freeStore = static_cast<Screen*>(p);
}

void Test1() {
    cout << sizeof(AirplaneRep) << endl;
    AirplaneRep* p[10];
    for (int i = 0; i < 10; i++) {
        p[i] = new AirplaneRep;
    }
    p[1]->set(1000, 'A');
    for (int i = 0; i < 10; i++) {
        cout << p[i] << endl;
    }
    for (int i = 0; i < 10; i++) {
        delete p[i];
    }
}

int main()
{
    Test1();
    return 0;
}

