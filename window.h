#ifndef WINDOW_HEADER
#define WINDOW_HEADER

#include <stdbool.h>

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

extern int const WINDOW_WIDTH;
extern int const WINDOW_HEIGHT;

/*
// Init window and SDL_VIDEO, SDL_image
*/
bool init(SDL_Window **g_window, SDL_Renderer **g_renderer);


#endif
