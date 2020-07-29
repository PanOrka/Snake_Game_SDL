#include "window.h"

int const WINDOW_WIDTH = 720;
int const WINDOW_HEIGHT = 720;

bool init(SDL_Window **g_window, SDL_Renderer **g_renderer) {
    bool success = true;

    if (SDL_Init(SDL_INIT_VIDEO) != 0) {
        printf("Couldn't initialize video. SDL Error: %s\n", SDL_GetError());
        success = false;
    } else {
        *g_window = SDL_CreateWindow("Snake Game", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
                                   WINDOW_WIDTH, WINDOW_HEIGHT, SDL_WINDOW_SHOWN);
        if (*g_window == NULL) {
            printf("Couldn't create window. SDL Error: %s\n", SDL_GetError());
            success = false;
        } else {
            *g_renderer = SDL_CreateRenderer(*g_window, -1, 0);
            if (*g_renderer == NULL) {
                printf("Couldn't initialize renderer. SDL Error: %s\n", SDL_GetError());
                success = false;
            } else {
                SDL_SetRenderDrawColor(*g_renderer, 0xFF, 0xFF, 0xFF, SDL_ALPHA_OPAQUE);
                SDL_RenderClear(*g_renderer);
                SDL_RenderPresent(*g_renderer);

                int image_flags = IMG_INIT_PNG;
                if (!(IMG_Init(image_flags) & image_flags)) {
                    printf("Couldn't initialize PNG. SDL_image Error: %s\n", IMG_GetError());
                }
            }
        }
    }

    return success;
}
