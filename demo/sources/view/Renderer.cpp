#include <SDL2/SDL2_gfxPrimitives.h>

#include "../utilities/SDL_macros.h"
#include "Renderer.h"


using namespace rharel::efficient_reformation::demo;


Renderer::Renderer(const Style style) : style(style) {}

void Renderer::set_context(SDL_Renderer& value) { context = &value; }

bool Renderer::draw_vehicle(const Sint16 x, const Sint16 y)
{
    if (!context) { return false; }

    const Sint16 r = style.vehicle_radius;

    int status;
    // Draw fill:
    status = filledEllipseColor(context, 
                                x, y, r, r, 
                                style.vehicle_fill_color);
    SDL_CHECK(status, false);
    // Draw outline:
    status = ellipseColor(context,
                          x, y, r, r,
                          style.vehicle_outline_color);
    SDL_CHECK(status, false);

    return true;
}
