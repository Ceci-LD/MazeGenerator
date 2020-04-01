#include "Grid.h"

Grid::Grid(int rows, int cols, int cellWidth)
:   rows(rows)
,   cols(cols)
{
    maxSize = rows * cols;
    this->cellWidth = cellWidth;

    for(int y = 0; y < rows; y++)
    {
        for(int x = 0; x < cols; x++)
        {
            cells.push_back(new Cell(x, y, cellWidth));
        }
    }

    current = cells[getIndex(0, 0, cols)]; //Top Left
    current->visited = true;
    current->setState(State::Current);

    startingCell = cells[getIndex(0, 0, cols)];
    startingCell->gCost = 0;
    targetCell = cells[getIndex(cols - 1, rows - 1, cols)];

    openSet = new Heap(rows * cols);
    closedSet = new Heap(rows * cols);
    openSet->add(startingCell);
}

Cell* Grid::checkNeighbours(Cell* cell)
{
    std::vector<Cell*> neighbors;

    int x = cell->x;
    int y = cell->y;

    if(x >= 0 && x < cols && y-1 >= 0 && y-1 < rows){
        Cell* top       = cells[getIndex(x, y - 1, cols)];
        if(!top->visited)
            neighbors.push_back(top);
    }

    if(x+1 >= 0 && x+1 < cols && y >= 0 && y < rows){
        Cell* right     = cells[getIndex(x + 1, y, cols)];
        if(!right->visited)
            neighbors.push_back(right);
    }

    if(x >= 0 && x < cols && y+1 >= 0 && y+1 < rows){
        Cell* bottom    = cells[getIndex(x, y + 1, cols)];
        if(!bottom->visited)
            neighbors.push_back(bottom);
    }

    if(x-1 >= 0 && x-1 < cols && y >= 0 && y < rows){
        Cell* left      = cells[getIndex(x - 1, y, cols)];
        if(!left->visited)
            neighbors.push_back(left);
    }

    if(neighbors.size() > 0)
    {
        int result = (rand() % neighbors.size());
        return neighbors[result];
    }
    else
        return NULL;
}

void Grid::display(sf::RenderWindow &window)
{
    for(int i = 0; i < cells.size(); i++)
    {
        cells[i]->draw(window);
    }
}

int Grid::getIndex(int x, int y, int cols)
{
    return y * cols + x;
}

void Grid::removeWall(Cell* current, Cell* next)
{
    int x = current->x - next->x;
    int y = current->y - next->y;

    if(x == 1)
    {
        current->left = false;
        next->right = false;
        current->neighbours.push_back(next);
        next->neighbours.push_back(current);
    }
    else if(x == -1)
    {
        current->right = false;
        next->left = false;
        current->neighbours.push_back(next);
        next->neighbours.push_back(current);
    }

    if(y == 1)
    {
        current->top = false;
        next->bottom = false;
        current->neighbours.push_back(next);
        next->neighbours.push_back(current);
    }
    else if(y == -1)
    {
        current->bottom = false;
        next->top = false;
        current->neighbours.push_back(next);
        next->neighbours.push_back(current);
    }
}

void Grid::generateMaze()
{
    Cell* neighbor = checkNeighbours(current);

    if(neighbor != NULL)
    {
        neighbor->visited = true;
        neighbor->setState(State::Visited);

        cellStack.push(current);
        //Remove walls
        removeWall(current, neighbor);

        current->setState(State::Visited);
        current = neighbor;
        current->setState(State::Current);
    }
    else if(cellStack.size() > 0)
    {
        Cell* cell = cellStack.top();
        cellStack.pop();
        current = cell;
        current->setState(State::Current);
    }
    else
    {
        isMazeGenerated = true;
        resetGridState();
    }
}

void Grid::resetGridState()
{
    for(int i = 0; i < cells.size(); i++)
    {
        cells[i]->setState(State::Neutral);
    }
}


void Grid::findPath()
{
    startingCell->setState(State::Start);
    targetCell->setState(State::Target);

    if(openSet->count() > 0)
    {
        //TO:DO Algorithm
        Cell* curr = openSet->removeFirst();
        closedSet->add(curr);

        //Exit
        if(curr == targetCell || isPathFound)
        {
            //TO:DO display path
            if(!isPathFound)
            {
                while(curr != NULL)
                {
                    path.push_back(curr);
                    curr = curr->parent;
                }

                std::reverse(path.begin(), path.end());

                startingCell->setState(State::Start);

                isPathFound = true;
            }

            return;
        }

        std::vector<Cell*> neighbours = curr->neighbours;
        for(int i = 0; i < neighbours.size(); i++)
        {
            int tentative_gCost = curr->gCost + heuristics(curr, neighbours[i]);

            if(tentative_gCost < neighbours[i]->gCost)
            {
                if(!closedSet->contains(neighbours[i]))
                {
                    neighbours[i]->parent = curr;
                    neighbours[i]->gCost = tentative_gCost;

                    if(!openSet->contains(neighbours[i]))
                    {
                        openSet->add(neighbours[i]);
                    }
                }
            }
        }

        for(int i = 0; i < openSet->count(); i++)
        {
            openSet->getItem(i)->setState(State::Current);
        }
        for(int i = 0; i < closedSet->count(); i++)
        {
            closedSet->getItem(i)->setState(State::Visited);
        }

    }

}

int Grid::heuristics(Cell* a, Cell* b)
{
    int xDist = abs(b->x - a->x);
    int yDist = abs(b->y - a->y);

    return xDist + yDist;
}


void Grid::getPath()
{
    if(iteratorIndex < path.size())
    {
        path[iteratorIndex]->setState(State::Path);
        iteratorIndex++;
    }

    if(iteratorIndex == path.size())
        isAlgFinished = true;
}














