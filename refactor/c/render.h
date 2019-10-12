#ifndef render_
#define render_ 1
#include "main.h"

struct animation {
    explosion *e;
};

struct renderer {
    SDL_Window *w;
    SDL_Renderer *r;
    state *s;
    list *ongoing;
    int width;
    int height;
};

struct base 
{
    renderer *r;
    state *s;
    int running;
};


renderer *alloc_renderer(state*,int,int);
void dealloc_renderer(renderer*);
base* alloc_base(int width,int height,int rows,int cols,player *players,int size);
void dealloc_base(base *b);
void draw_grid(renderer *r,color c,int rows,int cols);
void run(base *b);
void mouse_event(base *b,SDL_Event *e);
void update_state(base *b,int i,int j);
#endif