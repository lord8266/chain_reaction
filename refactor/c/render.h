#ifndef render_
#define render_ 1
#include "main.h"
#include <SDL.h>

struct animation {
    explosion *e;

};

struct render {
    SDL_Window *w;
    SDL_Renderer *r;
    state *s;
    list ongoing;
};
#endif