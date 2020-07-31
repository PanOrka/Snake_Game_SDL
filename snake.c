#include "snake.h"

#include "stdlib.h"
#include "time.h"

#ifndef SNAKE_FRAME
#define SNAKE_FRAME 0
#endif

#ifndef SET_COLOR_WHITE
#define SET_COLOR_WHITE SDL_SetRenderDrawColor(g_renderer, 0xFF, 0xFF, 0xFF, SDL_ALPHA_OPAQUE)
#endif

#ifndef SET_COLOR_BLACK
#define SET_COLOR_BLACK SDL_SetRenderDrawColor(g_renderer, 0x00, 0x00, 0x00, SDL_ALPHA_OPAQUE)
#endif

#ifndef SET_COLOR_RED
#define SET_COLOR_RED SDL_SetRenderDrawColor(g_renderer, 0xFF, 0x00, 0x00, SDL_ALPHA_OPAQUE);
#endif

#ifndef SET_COLOR_GREEN
#define SET_COLOR_GREEN SDL_SetRenderDrawColor(g_renderer, 0x00, 0xFF, 0x00, SDL_ALPHA_OPAQUE);
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
    s_head->snake_grow = 0;

    s_body->next = NULL;
    s_body->x = s_head->x - 1*TILE_SIZE;
    s_body->y = s_head->y;
    s_body->snake_grow = 0;
}

void snake_reset(snake_head *s_head, snake_body **s_body) {
    snake_body *temp = *s_body;
    while (temp->next != NULL) {
        snake_body *ptr_to_free = temp;
        temp = temp->next;
        free(ptr_to_free);
    }

    *s_body = temp;
    snake_init(s_head, *s_body);
}

void snake_move(snake_head *s_head, snake_body **s_body, snake_apple *s_apple) {
    snake_body *temp = *s_body;
    short new_head_pos_x = s_head->x + s_head->vel_x * TILE_SIZE;
    short new_head_pos_y = s_head->y + s_head->vel_y * TILE_SIZE;
    if (new_head_pos_y >= WINDOW_HEIGHT || new_head_pos_y < 0 || new_head_pos_x >= WINDOW_WIDTH || new_head_pos_x < 0) {
        s_apple->was_eaten = true;
        return snake_reset(s_head, s_body);
    }

    if (temp->snake_grow) {
        snake_body *new_node = malloc(sizeof(snake_body));
        new_node->next = *s_body;
        new_node->x = temp->x;
        new_node->y = temp->y;
        new_node->snake_grow = 0;

        *s_body = new_node;
    }
    if (new_head_pos_x == temp->x && new_head_pos_y == temp->y) {
        s_apple->was_eaten = true;
        return snake_reset(s_head, s_body);
    }

    while (temp->next != NULL) {
        temp->x = temp->next->x;
        temp->y = temp->next->y;
        temp->snake_grow = temp->next->snake_grow;
        if (new_head_pos_x == temp->x && new_head_pos_y == temp->y) {
            s_apple->was_eaten = true;
            return snake_reset(s_head, s_body);
        }

        temp = temp->next;
    }
    temp->x = s_head->x;
    temp->y = s_head->y;
    temp->snake_grow = s_head->snake_grow;

    s_head->x = new_head_pos_x;
    s_head->y = new_head_pos_y;
    s_head->snake_grow = 0;

    if (!s_apple->was_eaten && s_head->x == s_apple->x && s_head->y == s_apple->y) {
        s_apple->was_eaten = true;
        s_head->snake_grow = 1;
    }
}

void render_snake(SDL_Renderer *g_renderer, snake_head *s_head, snake_body *s_body, snake_apple *s_apple) {
    SDL_Rect clip = {0, 0, TILE_SIZE - 2*SNAKE_FRAME, TILE_SIZE - 2*SNAKE_FRAME};

    SET_COLOR_WHITE;

    clip.x = s_head->x + SNAKE_FRAME;
    clip.y = s_head->y + SNAKE_FRAME;
    SDL_RenderFillRect(g_renderer, &clip);

    while (s_body != NULL) {
        clip.x = s_body->x + SNAKE_FRAME;
        clip.y = s_body->y + SNAKE_FRAME;

        if (s_body->snake_grow) {
            SET_COLOR_GREEN;
            SDL_RenderFillRect(g_renderer, &clip);
            SET_COLOR_WHITE;
        } else {
            SDL_RenderFillRect(g_renderer, &clip);
        }

        s_body = s_body->next;
    }

    if (!s_apple->was_eaten) {
        SET_COLOR_RED;
        clip.x = s_apple->x + SNAKE_FRAME;
        clip.y = s_apple->y + SNAKE_FRAME;

        SDL_RenderFillRect(g_renderer, &clip);
    }

    SET_COLOR_BLACK;
}

struct vector {
    short x, y;
};

struct vector random_position() {
    unsigned short tiles_in_axis = WINDOW_HEIGHT/TILE_SIZE;
    srand(time(NULL));
    struct vector pos_vec = {(rand() % tiles_in_axis)*TILE_SIZE, (rand() % tiles_in_axis)*TILE_SIZE};

    return pos_vec;
}

void spawn_apple(snake_apple *s_apple, snake_head *s_head, snake_body *s_body) {
    struct vector new_pos = random_position();

    if (s_head->x != new_pos.x && s_head->y != new_pos.y) {
        while (s_body != NULL) {
            if (s_body->x == new_pos.x && s_body->y == new_pos.y) {
                return;
            } else {
                s_body = s_body->next;
            }
        }

        s_apple->x = new_pos.x;
        s_apple->y = new_pos.y;
        s_apple->was_eaten = false;
    }
}
