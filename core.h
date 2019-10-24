#ifndef core_
#define core_
#include "main.h"

 struct pos {
   int row;
   int col;
};

struct color {
  Uint8 r,g,b,a;
};

 struct box {
    int player;
    pos position;
    int atoms;
    int max;
    pos surrounding[4];
    int index[4];
};

 struct layout {

   int rows;
   int cols;
   box *boxes; 
};


 struct state {
  layout *board;
  list *ongoing;
  // update_func update;
  player *players;
  int *alive;
  int curr;
  int n_players;
  int completed;
  base *b;
  stack *checkpoints;
  void* prev;

  int save_box_size;
  int save_player_size;
  int save_alive_size;
};

struct player {
  int start;
  color c;
  int n;
};

struct explosion {
    pos from;
    pos to;
    int player;
    int completed;
};


layout *alloc_layout(int rows,int cols);
state *alloc_state(int,int,player *players,int size,base *b);
player *alloc_player(color c);
void save_state(base*);

void dealloc_layout(layout *l);
void dealloc_box(box *b);
void dealloc_player(player *p);
void dealloc_state(state *s);

void write_box(box *b,int row,int col,int max,pos *p,int *index);
void write_player(player *p,color);
void write_explosion(explosion *e,pos from,pos to,int player);

int step(state *s);
int add(state *s,int i,int j,int player,int force);
int continue_game(state *s,int i,int j);
void update(state *s,int,int);
void cycle(state *s);

void checkpoint(base *b);
int rollback(base *b);

//debug
void print_layout(layout *l);
void print_atoms(layout *l);
void complete(state *s);


#endif