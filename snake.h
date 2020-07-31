#ifndef SNAKE_HEADER
#define SNAKE_HEADER

#include <SDL2/SDL.h>

#include <stdbool.h>

typedef struct snake_head snake_head;

struct snake_head {
    short x, y;
    short vel_x : 2;
    short vel_y : 2;
    unsigned short snake_grow : 1;
};

typedef struct snake_body snake_body;

struct snake_body {
    snake_body *next;
    short x, y;
    unsigned short snake_grow : 1;
};

struct snake_textures {
    SDL_Texture *background;
    SDL_Texture *head[4];
    SDL_Texture *body[4];
    SDL_Texture *tail[4];
};

typedef struct snake_textures snake_textures;

/*
// Apple structure
*/
struct snake_apple {
    short x, y;
    bool was_eaten;
};

typedef struct snake_apple snake_apple;

/*
// Init snake
*/
void snake_init(snake_head *s_head, snake_body *s_body);

/*
// Clear snake body 
*/
void snake_reset(snake_head *s_head, snake_body **s_body);

/*
// Snake movement
*/
void snake_move(snake_head *s_head, snake_body **s_body, snake_apple *s_apple);

/*
// Render snake
*/
void render_snake(SDL_Renderer *g_renderer, snake_head *s_head, snake_body *s_body, snake_apple *s_apple, snake_textures *s_textures);

/*
// Apple spawner
*/
void spawn_apple(snake_apple *s_apple, snake_head *s_head, snake_body *s_body);

#endif
