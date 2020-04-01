#ifndef APPLICATION_H_INCLUDED
#define APPLICATION_H_INCLUDED

#include <SFML/Graphics.hpp>

#include "Grid.h"
#include "Timer.h"

constexpr int WIDTH = 600, HEIGHT = 600;

class Application
{
    private:
        void pollEvents();
        void update();
        sf::RenderWindow _window;

        Grid* grid;
        int cellWidth;

        bool startPathFinding = false;
        bool isTimerDestroyed = false;

    public:
        Application();

        void run();

        Timer::Timer* timer;
};

#endif // APPLICATION_H_INCLUDED
