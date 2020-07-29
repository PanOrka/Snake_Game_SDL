#include "game.h"


void run(SDL_Window *g_window, SDL_Renderer *g_renderer) {
    bool quit = false;
    SDL_Event e;
    while (!quit) {
        while (SDL_PollEvent(&e) != 0) {
            if (e.type == SDL_QUIT) {
                quit = true;
            }
        }
    }
}
