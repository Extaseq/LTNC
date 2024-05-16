#include "Timer.h"

Timer* Timer::sInstance = nullptr;

Timer* Timer::Instance()
{
    if (sInstance == nullptr)
    {
        sInstance = new Timer();
    }
    return sInstance;
}

void Timer::Release()
{
    delete sInstance;
    sInstance = nullptr;
}

Timer::Timer() {}

Timer::~Timer() {}

Uint64 Timer::Now()
{
    Time_Point current = Clock::now();

    mSeconds time = std::chrono::duration_cast<mSeconds>(current.time_since_epoch());

    return static_cast<Uint64>(time.count());
}

std::string Timer::GetDate()
{
    Time_Point current = Clock::now();

    std::time_t time = Clock::to_time_t(current);

    return std::ctime(&time);
}