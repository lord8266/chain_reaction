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
    float speed;
    float curr_pos[2];
    float end_pos[2];
    int direction;
    int type;
};

struct box_renderer {
    box *b;
    float rotation;
    float speed;
    int direction;
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
void dealloc_animation(animation *a);
void dealloc_renderer(renderer*);
void dealloc_textures(textures *);
base* alloc_base(int box_size,int rows,int cols,player *players,int size);
void dealloc_base(base *b);
textures* alloc_textures();
animation* alloc_animation(explosion *e,float speed);

void new_animation(base *b,explosion *e,float speed);
int update_animation(animation *a);
node* delete_animation(base *b,node *a);

int mouse_event(base *b,SDL_Event *e);
int update_state(base *b,int i,int j);

void draw_atoms(base *b);
void render_box(box_renderer *br,int i,int j,textures *tr,player *p,SDL_Renderer *r);
void draw_grid(renderer *r,color c,int rows,int cols);

void run(base *b);

#endif