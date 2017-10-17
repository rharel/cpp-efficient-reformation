#include <thread>

#include <glm/gtc/matrix_transform.hpp>
#include <glm/vec2.hpp>
#include <glm/vec3.hpp>

#include "../utilities/SDL_macros.h"
#include "Application.h"


using namespace rharel::efficient_reformation::core;
using namespace rharel::efficient_reformation::demo;


const Renderer::Style DEFAULT_RENDERING_STYLE =
{
    /* vehicle fill color:    */ 0xFFC00000,  // 0xAABBGGRR
    /* vehicle outline color: */ 0xFFC0C0C0,
    /* vehicle radius:        */ 4
};
Application::Application(const std::string& title,
                         const unsigned int window_width,
                         const unsigned int window_height,
                         const unsigned int vehicle_count)
    : gui { title, window_width, window_height },
      scene(Vehicle 
           { 
               /* position: */ glm::vec2(),
               /* target:   */ glm::vec2(), 
               /* speed:    */ 30
           }, 
           vehicle_count),
      renderer(DEFAULT_RENDERING_STYLE)
{
    const float s = DEFAULT_RENDERING_STYLE.vehicle_radius;
    const float tx = 0.5f * window_width,
                ty = 0.5f * window_height;
    transform = glm::mat3(s , 0 , 0 , 
                          0 , s , 0 ,
                          tx, ty, 1 );
}

bool Application::launch()
{
    if (was_launched) { return false; }
    else
    {
        was_launched = true;

        return initialize_graphics() &&
               run_main_loop();
    }
}

bool Application::initialize_graphics()
{
    gui.window = SDL_CreateWindow(gui.title.data(),
                                  /* x: */ SDL_WINDOWPOS_CENTERED,  
                                  /* y: */ SDL_WINDOWPOS_CENTERED,
                                  gui.width, gui.height,
                                  SDL_WINDOW_SHOWN);
    SDL_CHECK_NULL(gui.window, false);

    gui.surface = SDL_GetWindowSurface(gui.window);
    SDL_CHECK_NULL(gui.surface, false);

    gui.context = SDL_CreateRenderer(gui.window, -1, 0);
    SDL_CHECK_NULL(gui.context, false);

    renderer.set_context(*gui.context);

    return true;
}

bool Application::run_main_loop()
{
    static const unsigned int FRAMES_PER_SECOND = 30;
    static const double       FRAME_INTERVAL    = 1.0 / FRAMES_PER_SECOND;

    bool no_errors = true;

    Stopwatch scene_stopwatch,  // Measures time between steps.
              frame_stopwatch;   // Measures time between frames.

    scene_stopwatch.start();

    while ((no_errors = handle_gui_events()) == true)
    {
        frame_stopwatch.start();

        if (render_simulation())
        {
            scene_stopwatch.stop();
            scene.step(static_cast<float>(
                /* duration: */ scene_stopwatch.get_elapsed_seconds()
            ));
            scene_stopwatch.start();
        }

        // Check how much time we have left for the current frame: 
        frame_stopwatch.stop();
        const double surplus_seconds = (
            FRAME_INTERVAL - frame_stopwatch.get_elapsed_seconds()
        );
        if (surplus_seconds > 0)
        { 
            // We have been assigned a set amount of time for the current 
            // frame, but have not used up all of it. To put a cap on the 
            // rendering framerate, we spend the surplus idly:
            SDL_Delay(static_cast<Uint32>(/* ms: */ surplus_seconds * 1000)); 
        }
    }
    scene.destroy();
    
    SDL_DestroyWindow(gui.window);
    
    return no_errors;
}

bool Application::handle_gui_events()
{
    static const char KEY_CYCLE_FORMATION = SDLK_c,
                      KEY_QUIT            = SDLK_ESCAPE;

    SDL_Event event;
    while (SDL_PollEvent(&event))
    {
        switch (event.type)
        {
            case SDL_QUIT: { return false; }
            case SDL_KEYUP: 
            {
                switch (event.key.keysym.sym)
                {
                    case KEY_QUIT:            { return false; }
                    case KEY_CYCLE_FORMATION: { scene.next_formation(); }
                }
                break;
            }
        }
    }
    return true;
}

bool Application::render_simulation()
{
    if (!draw_background()) { return false; }
    
    const World& world = scene.get_world();
    for (unsigned int i = 0; i < world.get_vehicle_count(); ++i)
    {
        using glm::vec2; 
        using glm::vec3;
        
        const vec2& p_w = world.get_vehicle(i).position,  // World space.
                    p_s = transform * vec3(p_w, 1);       // Screen space.


        if (!renderer.draw_vehicle(static_cast<Sint16>(p_s.x), 
                                   static_cast<Sint16>(p_s.y))) 
        { 
            return false; 
        }
    }
    SDL_RenderPresent(gui.context);

    return true;
}

bool Application::draw_background()
{
    SDL_CHECK(SDL_SetRenderDrawColor(gui.context, 255, 255, 255, 255), false);
    SDL_CHECK(SDL_RenderClear(gui.context), false);

    return true;
}
