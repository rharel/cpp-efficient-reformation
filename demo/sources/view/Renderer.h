#pragma once

#include <SDL2/SDL.h>


namespace rharel::efficient_reformation::demo
{
    /// Renders the state of a simulation.
    class Renderer
    {
        public:
        /// Drawing style properties.
        struct Style
        {
            /// Vehicle fill color (0xAABBGGRR).
            Uint32 vehicle_fill_color;
            /// Vehicle outline color (0xAABBGGRR).
            Uint32 vehicle_outline_color;
            /// Vehicle radius in pixels.
            Sint16 vehicle_radius;
        };
        /// Creates a new renderer using the specified style.
        explicit Renderer(Style style);

        /// Sets the target drawing context.
        void set_context(SDL_Renderer& context);

        /// Draws a vehicle centered at the specified pixel.
        ///
        /// Returns true iff successful. Has no effect if no drawing context
        /// has been set.
        bool draw_vehicle(Sint16 x, Sint16 y);

        private:
        SDL_Renderer* context = nullptr;
        const Style  style;
    };
}
