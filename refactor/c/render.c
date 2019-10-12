#include "main.h"

renderer *alloc_renderer(state *s,int width,int height) {
    renderer *r = malloc(sizeof(renderer));
    r->s = s;
    s->r = r;
    r->width = width;
    r->height = height;
    SDL_Init(SDL_INIT_EVERYTHING);
    r->w = SDL_CreateWindow("chainreaction2d",SDL_WINDOWPOS_CENTERED,SDL_WINDOWPOS_CENTERED,
    width,height,SDL_WINDOW_SHOWN);
    r->r = SDL_CreateRenderer(r->w,-1,SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    r->ongoing = alloc_list();
    return r;
}

void dealloc_renderer(renderer *r) {
    SDL_Quit();
    dealloc_list(r->ongoing);
    free(r);    
}

void draw_grid(renderer *r,color c,int rows,int cols) {
    SDL_SetRenderDrawColor(r->r,c.r,c.g,c.b,c.a);
    SDL_RenderDrawLine(r->r,0,1,r->width,1);
    SDL_RenderDrawLine(r->r,0,r->height-1,r->width,r->height-1);

    SDL_RenderDrawLine(r->r,1,0,r->height,1);
    SDL_RenderDrawLine(r->r,r->width-1,0,r->width-1,r->height);

    for (int i=1;i<rows;i++) {
        SDL_RenderDrawLine(r->r,0,i*(r->height/rows),r->width,i*(r->height/rows) );
    }
    for (int i=1;i<cols;i++) {
        SDL_RenderDrawLine(r->r,i*(r->width/cols),0,i*(r->width/cols),r->height );
    }

}

void mouse_event(base *b,SDL_Event *e) {
    float _r,_c;
    _r = (e->button.y+0.0)/b->r->height*b->s->board->rows;
    _c = (e->button.x+0.0)/b->r->width*b->s->board->cols;
    int r = (int)_r,c=(int)_c;
    printf("%d %d\n",r,c);
    update_state(b,r,c);

}

void update_state(base *b,int i,int j) {
    int r = continue_game(b->s,i,j);
    if (r) {
        putchar('\n');
        print_atoms(b->s->board);
        putchar('\n');
        printf("%d\n",b->s->curr);
    }
    else {
        printf("\nUnavailable\n\n");
    }
}
void run(base *b) {
    SDL_Event e;
    while(SDL_PollEvent(&e)) {
        if (e.type==SDL_QUIT) {
            b->running = 0;
        }
        else if (e.type==SDL_MOUSEBUTTONDOWN) {
            mouse_event(b,&e);
        }
    }
    color c = {255,0,0,255};

    SDL_SetRenderDrawColor(b->r->r,0,0,0,0);
    SDL_RenderClear(b->r->r);

    draw_grid(b->r,c,b->s->board->rows,b->s->board->rows);

    SDL_RenderPresent(b->r->r);
}
base* alloc_base(int width,int height,int rows,int cols,player *players,int size) {
    base *b = malloc(sizeof(base));
    b->s = alloc_state(rows,cols,players,size);
    b->r = alloc_renderer(b->s,width,height);
    b->running = 1;
    return b;
} 

void dealloc_base(base *b) {
    dealloc_renderer(b->r);
    dealloc_state(b->s);
    free(b);
}
