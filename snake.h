#ifndef SNAKE_HEADER
#define SNAKE_HEADER

#include <SDL2/SDL.h>

typedef struct snake_body snake_body;

struct snake_head {
    short x, y;
    short vel_x : 2;
    short vel_y : 2;
};

typedef struct snake_head snake_head;

struct snake_body {
    snake_body *next;
    short x, y;
};

struct snake_textures {
    SDL_Texture *background;
    SDL_Texture *head;
    SDL_Texture *body;
    SDL_Texture *tail;
};

typedef struct snake_textures snake_textures;

/*
// Init snake
*/
void snake_init(snake_head *s_head, snake_body *s_body);

/*
// Render snake
*/
void render_snake(SDL_Renderer *g_renderer, snake_head *s_head, snake_body *s_body, snake_textures *s_textures);

#endif
