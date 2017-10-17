#include "Stopwatch.h"


using namespace rharel::efficient_reformation::demo;


const Uint64 COUNT_FREQUENCY = SDL_GetPerformanceFrequency();


void Stopwatch::reset() { start_count = elapsed_count = 0; }
void Stopwatch::start() { start_count = SDL_GetPerformanceCounter(); }
void Stopwatch::stop()
{
    elapsed_count = SDL_GetPerformanceCounter() - start_count;
}

double Stopwatch::get_elapsed_seconds() const
{
    return static_cast<double>(elapsed_count) /
           static_cast<double>(COUNT_FREQUENCY);
}
double Stopwatch::get_elapsed_milliseconds() const
{
    return static_cast<double>(elapsed_count * 1000) /
           static_cast<double>(COUNT_FREQUENCY);
}
