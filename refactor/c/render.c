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

    layout *board = s->board;
    int size = board->cols*board->rows;
    r->br =malloc(sizeof(box_renderer)*board->cols*board->rows);

    for (int i=0;i<size;i++) {
        r->br[i].b = &board->boxes[i];
        r->br[i].rotation = r->br->speed = 0;
    }
    return r;
}

void render_box(box_renderer *br,int i,int j,textures *tr,player *p,SDL_Renderer *r) {
    box *b = br->b;
    int a = b->atoms;

    color c = p->c;
    switch (a)
    {
    case 1:
        tr->rect.x = j*tr->rect.w;
        tr->rect.y = i*tr->rect.h;
        SDL_SetTextureColorMod(tr->one,c.r,c.g,c.b);
        SDL_RenderCopy(r,tr->one,NULL,&tr->rect);
        break;

    case 2:
        tr->rect.x = j*tr->rect.w;
        tr->rect.y = i*tr->rect.h;
        SDL_SetTextureColorMod(tr->two,c.r,c.g,c.b);
        SDL_RenderCopy(r,tr->two,NULL,&tr->rect);
        break;

    case 3:
        tr->rect.x = j*tr->rect.w;
        tr->rect.y = i*tr->rect.h;
        SDL_SetTextureColorMod(tr->three,c.r,c.g,c.b);
        SDL_RenderCopy(r,tr->three,NULL,&tr->rect);
        break;

    default:
        break;
    }
}



void dealloc_renderer(renderer *r) {
    SDL_Quit();
    dealloc_list(r->ongoing);
    free(r->br);
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

void draw_atoms(base *b) {
    box_renderer *br = b->r->br;
    int rows = b->s->board->rows;
    int cols = b->s->board->cols;
    for (int i=0;i<rows;i++) {
        for (int j=0;j<cols;j++) {
            box_renderer *curr_box = &br[i*cols +j];
            int p =curr_box->b->player;
            if (p!=-1 && curr_box->b->atoms>0) {
                player *p_struct = &b->s->players[p];
                render_box(&b->r->br[i*cols+j],i,j,b->t,p_struct,b->r->r);
            }
        }
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
    color c = b->s->players[ b->s->curr].c;

    SDL_SetRenderDrawColor(b->r->r,0,0,0,0);
    SDL_RenderClear(b->r->r);

    draw_grid(b->r,c,b->s->board->rows,b->s->board->rows);
    draw_atoms(b); 
    SDL_RenderPresent(b->r->r);

} SDL_Texture *two;
    SDL_Texture *three;
base* alloc_base(int width,int height,int rows,int cols,player *players,int size) {
    base *b = malloc(sizeof(base));
    b->s = alloc_state(rows,cols,players,size);
    b->r = alloc_renderer(b->s,width,height);
    b->t = alloc_textures(b);
    b->running = 1;
    return b;
} 

void dealloc_base(base *b) {
    dealloc_renderer(b->r);
    dealloc_state(b->s);
    dealloc_textures(b->t);
    free(b);
}

textures* alloc_textures(base *b) {
    IMG_Init(IMG_INIT_PNG);
    textures *t = malloc(sizeof(textures));
    SDL_Surface *s  =  IMG_Load("textures/final/one_white.png");
    t->one = SDL_CreateTextureFromSurface(b->r->r,s);
    SDL_FreeSurface(s);
    s = IMG_Load("textures/final/two_white.png");
    t->two = SDL_CreateTextureFromSurface(b->r->r,s);
    SDL_FreeSurface(s);
    s = IMG_Load("textures/final/three_white.png");
    t->three = SDL_CreateTextureFromSurface(b->r->r,s);
    SDL_FreeSurface(s);
    s = IMG_Load("textures/final/one_glow_white.png");
    t->glow = SDL_CreateTextureFromSurface(b->r->r,s);
    SDL_FreeSurface(s);
    t->rect.w = b->r->width/b->s->board->cols;
    t->rect.h = b->r->height/b->s->board->rows;
    return t;
}

void dealloc_textures(textures *t) {
    SDL_DestroyTexture(t->one);
    SDL_DestroyTexture(t->two);
    SDL_DestroyTexture(t->three);
    SDL_DestroyTexture(t->glow);
    IMG_Quit();
    free(t);
}
