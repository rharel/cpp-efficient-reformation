#pragma once

#include <SDL2/SDL.h>


namespace rharel::efficient_reformation::demo
{
    /// Measures time interval duration.
    class Stopwatch
    {
        public:
        /// Resets the watch.
        void reset();
        /// Starts the watch.
        void start();
        /// Stops the watch. The elapsed time is accessible through  the
        /// get_elapsed_*() family of methods.
        void stop();

        /// Gets the duration of the last measured interval (in seconds).
        double get_elapsed_seconds() const;
        /// Gets the duration of the last measured interval (in milliseconds).
        double get_elapsed_milliseconds() const;

        private:
        Uint64 start_count, elapsed_count;
    };
}
