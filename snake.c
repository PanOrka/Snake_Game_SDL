#include "snake.h"

#ifndef SNAKE_FRAME
#define SNAKE_FRAME 2
#endif

#ifndef SET_COLOR_BLACK
#define SET_COLOR_BLACK SDL_SetRenderDrawColor(g_renderer, 0xFF, 0xFF, 0xFF, SDL_ALPHA_OPAQUE)
#endif

#ifndef SET_COLOR_WHITE
#define SET_COLOR_WHITE SDL_SetRenderDrawColor(g_renderer, 0x00, 0x00, 0x00, SDL_ALPHA_OPAQUE)
#endif

extern unsigned short const WINDOW_WIDTH;
extern unsigned short const WINDOW_HEIGHT;
extern unsigned short const TILE_SIZE;

void snake_init(snake_head *s_head, snake_body *s_body) {
    unsigned short tiles_in_axis = WINDOW_HEIGHT/TILE_SIZE;

    s_head->x = (tiles_in_axis/2)*TILE_SIZE;
    s_head->y = (tiles_in_axis/2)*TILE_SIZE;
    s_head->vel_x = 1;
    s_head->vel_y = 0;

    s_body->next = NULL;
    s_body->x = s_head->x - 1*TILE_SIZE;
    s_body->y = s_head->y;
}

void render_snake(SDL_Renderer *g_renderer, snake_head *s_head, snake_body *s_body, snake_textures *s_textures) {
    SDL_Rect clip = {0, 0, TILE_SIZE - 2*SNAKE_FRAME, TILE_SIZE - 2*SNAKE_FRAME};

    SET_COLOR_BLACK;

    clip.x = s_head->x + SNAKE_FRAME;
    clip.y = s_head->y + SNAKE_FRAME;
    SDL_RenderFillRect(g_renderer, &clip);

    while (s_body != NULL) {
        clip.x = s_body->x + SNAKE_FRAME;
        clip.y = s_body->y + SNAKE_FRAME;

        SDL_RenderFillRect(g_renderer, &clip);
        s_body = s_body->next;
    }

    SET_COLOR_WHITE;
}
