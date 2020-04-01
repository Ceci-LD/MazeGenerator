#include "Cell.h"

Cell::Cell(int x, int y, int cellSize)
: x(x)
, y(y)
, cellSize(cellSize)
, visited(false)
{
    int borderWidth = 2;
    topWall.setSize(sf::Vector2f(cellSize, borderWidth));
    topWall.setPosition(sf::Vector2f(x * cellSize, y * cellSize));
    topWall.setFillColor(sf::Color::Black);

    rightWall.setSize(sf::Vector2f(cellSize, borderWidth));
    rightWall.setPosition(sf::Vector2f(x * cellSize + cellSize, y * cellSize));
    rightWall.setFillColor(sf::Color::Black);
    rightWall.rotate(90);

    bottomWall.setSize(sf::Vector2f(cellSize, borderWidth));
    bottomWall.setPosition(sf::Vector2f(x * cellSize, y * cellSize + cellSize));
    bottomWall.setFillColor(sf::Color::Black);

    leftWall.setSize(sf::Vector2f(cellSize, borderWidth));
    leftWall.setPosition(sf::Vector2f(x * cellSize, y * cellSize));
    leftWall.setFillColor(sf::Color::Black);
    leftWall.rotate(90);

    cellShape.setPosition(sf::Vector2f(x * cellSize, y * cellSize));
    cellShape.setSize(sf::Vector2f(cellSize, cellSize));
    cellShape.setFillColor(sf::Color::White);

    gCost = INFINITY;
    hCost = INFINITY;

}

void Cell::draw(sf::RenderWindow &window)
{
    window.draw(cellShape);

    if(top)
        window.draw(topWall);
    if(right)
        window.draw(rightWall);
    if(bottom)
        window.draw(bottomWall);
    if(left)
        window.draw(leftWall);
}

void Cell::setState(State state)
{
    switch(state)
    {
        case State::Current:
            cellShape.setFillColor(sf::Color::Blue);
            break;

        case State::Visited:
            cellShape.setFillColor(sf::Color::Magenta);
            break;

        case State::Neutral:
            cellShape.setFillColor(sf::Color::White);
            break;

        case State::Start:
            cellShape.setFillColor(sf::Color::Green);
            break;

        case State::Target:
            cellShape.setFillColor(sf::Color::Red);
            break;

        case State::Path:
            cellShape.setFillColor(sf::Color::Cyan);
            break;

        default:
            break;
    }
}




