#include <iostream>

#include <SDL2/SDL.h>

#include "logging.h"


using namespace rharel::efficient_reformation;


void demo::log_SDL_error(const char* file,
                         const int   line,
                         const char* caller)
{
    std::cerr << file << "(" << line << ")" << " => " << caller << ": "
              << "SDL error: " << "'" << SDL_GetError() << "'\n";
}
