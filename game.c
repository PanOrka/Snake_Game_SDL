#include "game.h"
#include "snake.h"

unsigned short const TILE_SIZE = 20;

// in ms
static unsigned short const DELTA_TIME = 100;

void run(SDL_Window *g_window, SDL_Renderer *g_renderer) {
    bool quit = false;
    bool move_done = true;
    unsigned int last_time = SDL_GetTicks();

    SDL_Event e;
    snake_head *s_head = malloc(sizeof(s_head));
    snake_body *s_body = malloc(sizeof(s_body));

    snake_init(s_head, s_body);

    snake_apple s_apple = {-1, -1, true};

    SDL_RenderClear(g_renderer);
    render_snake(g_renderer, s_head, s_body, &s_apple, NULL);
    SDL_RenderPresent(g_renderer);

    while (!quit) {
        while (SDL_PollEvent(&e) != 0) {
            if (e.type == SDL_QUIT) {
                quit = true;
            } else if (move_done && e.type == SDL_KEYDOWN) {
                switch (e.key.keysym.sym) {
                    case SDLK_UP:
                        if (s_head->vel_y != 1) {
                            s_head->vel_x = 0;
                            s_head->vel_y = -1;
                        }
                        break;
                    case SDLK_DOWN:
                        if (s_head->vel_y != -1) {
                            s_head->vel_x = 0;
                            s_head->vel_y = 1;
                        }
                        break;
                    case SDLK_LEFT:
                        if (s_head->vel_x != 1) {
                            s_head->vel_x = -1;
                            s_head->vel_y = 0;
                        }
                        break;
                    case SDLK_RIGHT:
                        if (s_head->vel_x != -1) {
                            s_head->vel_x = 1;
                            s_head->vel_y = 0;
                        }
                        break;
                }

                move_done = false;
            }
        }

        if (SDL_GetTicks() - last_time >= DELTA_TIME) {
            // movement
            snake_move(s_head, &s_body, &s_apple);
            move_done = true;

            if (s_apple.was_eaten) {
                spawn_apple(&s_apple, s_head, s_body);
            }

            SDL_RenderClear(g_renderer);
            render_snake(g_renderer, s_head, s_body, &s_apple, NULL);
            SDL_RenderPresent(g_renderer);

            last_time = SDL_GetTicks();
        }
    }
}
