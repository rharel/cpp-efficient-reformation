#pragma once

#include <string>


namespace rharel::efficient_reformation::demo  
{
    /// Outputs the currently available SDL error message to std::cerr.
    void log_SDL_error(const char* file,
                       int         line,
                       const char* caller);
}
