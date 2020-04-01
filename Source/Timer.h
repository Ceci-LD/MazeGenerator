#ifndef TIMER_H_INCLUDED
#define TIMER_H_INCLUDED

#include <chrono>

namespace Timer
{

class Timer
{
private:
    std::chrono::time_point<std::chrono::high_resolution_clock> start_timepoint;

public:
    Timer()
    {
        start_timepoint = std::chrono::high_resolution_clock::now();
    }
    ~Timer()
    {
        Stop();
    }

    void Stop()
    {
        auto end_timepoint = std::chrono::high_resolution_clock::now();
        auto start = std::chrono::time_point_cast<std::chrono::microseconds>(start_timepoint).time_since_epoch().count();
        auto stop = std::chrono::time_point_cast<std::chrono::microseconds>(end_timepoint).time_since_epoch().count();

        auto duration = stop - start;

        double ms = duration * 0.001;
        std::cout << "PATH FOUND IN: " << ms << " ms\n";
    }

};

}

#endif // TIMER_H_INCLUDED
