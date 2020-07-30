#include "game.h"
#include "snake.h"

unsigned short const TILE_SIZE = 20;

// in ms
static unsigned short const DELTA_TIME = 33;

void run(SDL_Window *g_window, SDL_Renderer *g_renderer) {
    bool quit = false;
    unsigned int last_time = SDL_GetTicks();

    SDL_Event e;
    snake_head *s_head = malloc(sizeof(s_head));
    snake_body *s_body = malloc(sizeof(s_body));

    snake_init(s_head, s_body);

    SDL_RenderClear(g_renderer);
    render_snake(g_renderer, s_head, s_body, NULL);
    SDL_RenderPresent(g_renderer);

    while (!quit) {
        while (SDL_PollEvent(&e) != 0) {
            if (e.type == SDL_QUIT) {
                quit = true;
            }
        }

        if (SDL_GetTicks() - last_time >= DELTA_TIME) {
            SDL_RenderClear(g_renderer);
            render_snake(g_renderer, s_head, s_body, NULL);
            SDL_RenderPresent(g_renderer);

            // movement
            s_head->x += 1;
            s_head->y += 1;

            last_time = SDL_GetTicks();
        }
    }
}
