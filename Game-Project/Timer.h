#ifndef TIMER_H
#define TIMER_H

#include <chrono>

#include <string>

using Clock = std::chrono::high_resolution_clock;
using Time_Point = std::chrono::time_point<Clock>;
using mSeconds = std::chrono::milliseconds;

using Uint64 = uint64_t;

class Timer
{
private:

    static Timer* sInstance;

public:

    static Timer* Instance();

    static void Release();

    Uint64 Now();

    std::string GetDate();

private:

    Timer();

    ~Timer();

};

#endif // TIMER_H
