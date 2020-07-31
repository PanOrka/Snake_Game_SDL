#ifndef GAME_HEADER
#define GAME_HEADER

#include "snake.h"

#include <stdbool.h>

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

/*
// Main Game-Loop
*/
void run(SDL_Window *g_window, SDL_Renderer *g_renderer);

/*
// Free game memory and close
*/
void close_game(SDL_Window *g_window, SDL_Renderer *g_renderer, snake_head *s_head, snake_body *s_body);

#endif
