#include "window.h"
#include "game.h"

int main() {
    SDL_Window *g_window = NULL;
    SDL_Renderer *g_renderer = NULL;

    if (!init(&g_window, &g_renderer)) {
        exit(1);
    }
    run(g_window, g_renderer);
}
