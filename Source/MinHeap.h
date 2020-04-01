#ifndef MINHEAP_H_INCLUDED
#define MINHEAP_H_INCLUDED

#include <iostream>
#include <vector>

#include "Cell.h"

class Heap
{
private:
    std::vector<Cell*> items;
    int current_item_count;

public:
    Heap(int max_heap_size);

    void add(Cell* cell);

    void sortUp(Cell* cell);
    void sortDown(Cell* cell);

    void swapItems(Cell* a, Cell* b);

    Cell* removeFirst();

    void updateItem(Cell* cell);

    bool contains(Cell* cell);

    int count() { return current_item_count; }

    void displayHeap();

    Cell* getItem(int index);

};

#endif // MINHEAP_H_INCLUDED
