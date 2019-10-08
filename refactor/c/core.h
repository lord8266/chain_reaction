#ifndef core_
#define core_
#include "main.h"

 struct pos {
   int row;
   int col;
};

 struct box {
    int player;
    pos position;
    int atoms;
    int max;
    pos *surrounding;
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
    update_func update;
    player *players;
    int *alive;
};

struct player {
  int start;
  int color;
};

struct explosion {
    pos from;
    pos to;
    int player;
};
void write_box(box *b,int row,int col,int max,pos *p,int *index);
layout *alloc_layout(int rows,int cols);
void print_layout(layout *l);
void print_atoms(layout *l);
void dealloc_layout(layout *l);
void dealloc_box(box *b);
state *alloc_state(int,int,update_func);
void dealloc_state(state *s);
int step(state *s);
int add(state *s,int i,int j,int player,int force);
void complete(state *s);
void update(int,int);
#endif