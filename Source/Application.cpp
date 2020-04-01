#include "Application.h"

Application::Application()
:   _window({WIDTH, HEIGHT}, "Maze Generator")
{
    _window.setFramerateLimit(60);


    //Random # Generator
    //static std::minstd_rand randDevice(std::time(nullptr));
    //std::uniform_int_distribution<int> dist(0, 100);
    //int rand = randDevice(dist);

    cellWidth = 20;
    grid = new Grid(HEIGHT/cellWidth, WIDTH/cellWidth, cellWidth);
}

void Application::run()
{
    //Clear -> update -> draw -> display -> poll events
    while(_window.isOpen())
    {
        _window.clear(sf::Color::White);
        update();
        _window.display();
        pollEvents();
    }
}

void Application::pollEvents()
{
    sf::Event e;
    while(_window.pollEvent(e))
    {
        if(e.type == sf::Event::Closed)
        {
            _window.close();
        }

        if(e.type == sf::Event::KeyPressed)
        {
            if(e.key.code == sf::Keyboard::F)
            {
                timer = new Timer::Timer();
                startPathFinding = true;
            }
        }
    }
}

void Application::update()
{
    //Update/Draw
    if(!grid->isMazeGenerated)
        grid->generateMaze();

    if(grid->isMazeGenerated && startPathFinding)
        grid->findPath();

    if(grid->isPathFound)
        grid->getPath();

    if(grid->isAlgFinished)
    {
        if(!isTimerDestroyed)
        {
            delete timer;
            isTimerDestroyed = true;
        }
    }

    grid->display(_window);
}







