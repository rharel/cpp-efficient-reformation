#include <iostream>

#include <SDL2/SDL.h>

#include "utilities/SDL_macros.h"
#include "view/Application.h"


using namespace rharel::efficient_reformation::demo;


const int SUCCESS = 0,
          FAILURE = 1;
const int WINDOW_WIDTH  = 640, 
          WINDOW_HEIGHT = 480;


/// Application's entry point.
int main(int /* argc */, char** /* argv */)
{
    SDL_CHECK(SDL_Init(SDL_INIT_VIDEO), FAILURE);

    Application demo(/* title: */ "Efficient Reformation Demo",
                     WINDOW_WIDTH, WINDOW_HEIGHT);

    bool success = demo.launch();

    SDL_Quit();
    return success ? SUCCESS : FAILURE;
}
