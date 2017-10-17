#pragma once

#include <string>

#include <glm/mat3x3.hpp>
#include <SDL2/SDL.h>

#include "../model/Scene.h"
#include "Renderer.h"
#include "Stopwatch.h"


namespace rharel::efficient_reformation::demo
{
    /// Associates user actions with formation commands and displays the 
    /// result.
    class Application
    {
        public:
        /// Creates a new application to be launched.
        explicit Application(const std::string& title,
                             unsigned int window_width,
                             unsigned int window_height,
                             unsigned int vehicle_count = 100);

        /// Launches the application window and initiates the main event loop.
        ///
        /// Returns true iff the application was successfully launched, 
        /// executed, and closed.
        /// 
        /// Should be called at most once. Successive calls beyond the first 
        /// have no effect.
        bool launch();

        private:
        /// Initializes the window and drawing surface.
        ///
        /// Returns true iff successful.
        bool initialize_graphics();

        /// Runs the main event loop.
        ///
        /// Returns true iff successful.
        bool run_main_loop();

        /// Handles events of the graphical user interface.
        ///
        /// Returns true iff no 'quit' event was encountered.
        bool handle_gui_events();
        /// Renders the current state of the simulation onto the drawing 
        /// surface.
        ///
        /// Returns true iff successul.
        bool render_simulation();
        /// Fills the drawing surface with the background color.
        ///
        /// Returns true iff successful.
        bool draw_background();

        /// Graphical user interface properties.
        struct
        {
            std::string title;

            unsigned int width, height;

            SDL_Window*   window;
            SDL_Surface*  surface;
            SDL_Renderer* context;
        } gui;

        bool was_launched = false;

        Scene     scene;
        Renderer  renderer;
        
        glm::mat3 transform;
    };
}
