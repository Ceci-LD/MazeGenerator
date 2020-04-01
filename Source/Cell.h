#ifndef CELL_H_INCLUDED
#define CELL_H_INCLUDED

#include <SFML/Graphics.hpp>

enum class State
{
    Visited,
    Current,
    Neutral,
    Start,
    Target,
    Path
};

class Cell
{
public:
    int x, y;
    int cellSize;
    bool visited;

    int gCost;
    int hCost;
    std::vector<Cell*> neighbours;
    Cell* parent = NULL;

    int heapIndex = -1;


public:
    Cell(int x, int y, int cellSize);
    void draw(sf::RenderWindow &window);

    //walls
    bool top = true, right = true, bottom = true, left = true;
    sf::RectangleShape topWall;
    sf::RectangleShape rightWall;
    sf::RectangleShape bottomWall;
    sf::RectangleShape leftWall;

    sf::RectangleShape cellShape;

    void setState(State state);

    int fCost() { return gCost + hCost; }

};

#endif // CELL_H_INCLUDED
