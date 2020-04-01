#include "MinHeap.h"

Heap::Heap(int max_heap_size)
{
    items = std::vector<Cell*>(max_heap_size);
    current_item_count = 0;
}

void Heap::add(Cell* cell)
{
    cell->heapIndex = current_item_count;
    items[current_item_count] = cell;
    sortUp(cell);
    current_item_count++;
}

void Heap::sortUp(Cell* cell)
{
    int parentIndex = (cell->heapIndex - 1) / 2;

    while(true)
    {
        Cell* parentItem = items[parentIndex];
        if(cell->fCost() < parentItem->fCost())
        {
            swapItems(cell, parentItem);
        }
        else
        {
            break;
        }
    }
}

void Heap::sortDown(Cell* cell)
{
    while(true)
    {
        int leftIndex = cell->heapIndex * 2 + 1;
        int rightIndex = cell->heapIndex * 2 + 2;
        int swapIndex = 0;

        if(leftIndex < current_item_count)
        {
            swapIndex = leftIndex;

            if(rightIndex < current_item_count)
            {
                if(items[leftIndex]->fCost() > items[rightIndex]->fCost())
                {
                    swapIndex = rightIndex;
                }
            }

            if(cell->fCost() > items[swapIndex]->fCost())
            {
                swapItems(cell, items[swapIndex]);
            }
            else return;
        } else return;
    }
}

void Heap::swapItems(Cell* a, Cell* b)
{
    items[a->heapIndex] = b;
    items[b->heapIndex] = a;
    int itemAheapIndex = a->heapIndex;
    a->heapIndex = b->heapIndex;
    b->heapIndex = itemAheapIndex;
}

Cell* Heap::removeFirst()
{
    Cell* first = items[0];
    current_item_count--;

    items[0] = items[current_item_count];
    items[0]->heapIndex = 0;

    sortDown(items[0]);

    return first;
}

void Heap::updateItem(Cell* cell)
{
    sortUp(cell);
}

bool Heap::contains(Cell* cell)
{
    return items[cell->heapIndex] == cell ? true : false;
}

void Heap::displayHeap()
{
    for(int i = 0; i < current_item_count; i++)
    {
        std::cout << items[i]->x << ", " << items[i]->y << std::endl;
    }
}

Cell* Heap::getItem(int index)
{
    return items[index];
}












