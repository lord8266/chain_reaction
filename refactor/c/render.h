#ifndef render_
#define render_ 1
#include "main.h"

struct textures {
    SDL_Texture *one;
    SDL_Texture *two;
    SDL_Texture *three;
    SDL_Texture *glow;
    SDL_Rect rect;
};



struct animation {
    explosion *e;
};

struct box_renderer {
    box *b;
    int rotation;
    int speed;
};
struct renderer {
    SDL_Window *w;
    SDL_Renderer *r;
    box_renderer *br;
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
    textures *t;
};


renderer *alloc_renderer(state*,int,int);
void dealloc_renderer(renderer*);
base* alloc_base(int width,int height,int rows,int cols,player *players,int size);
void dealloc_base(base *b);
void draw_grid(renderer *r,color c,int rows,int cols);
void run(base *b);
void mouse_event(base *b,SDL_Event *e);
void update_state(base *b,int i,int j);
textures* alloc_textures();
void dealloc_textures(textures *);
void draw_atoms(base *b);
void render_box(box_renderer *br,int i,int j,textures *tr,player *p,SDL_Renderer *r);
#endif