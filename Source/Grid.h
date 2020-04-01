#ifndef GRID_H_INCLUDED
#define GRID_H_INCLUDED

#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include <random>
#include <ctime>
#include <stack>

#include "Cell.h"
#include "MinHeap.h"

class Grid
{
private:

    int rows, cols;
    int cellWidth;
    int maxSize;

    std::vector<Cell*> cells;
    std::stack<Cell*> cellStack;

    Heap* openSet;
    Heap* closedSet;
    Cell* startingCell;
    Cell* targetCell;
    int iteratorIndex = 0;

    std::vector<Cell*> path;

public:
    Grid(int rows, int cols, int cellWidth);

    Cell* checkNeighbours(Cell* cell);
    int getIndex(int x, int y, int cols);
    void display(sf::RenderWindow &window);

    void generateMaze();
    void removeWall(Cell* current, Cell* next);
    void resetGridState();

    void findPath();
    void getPath();
    int heuristics(Cell* a, Cell* b);

    Cell* current;



    bool isMazeGenerated = false;
    bool isPathFound = false;
    bool isAlgFinished = false;
};

#endif // GRID_H_INCLUDED
