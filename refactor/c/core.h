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
    // update_func update;
    player *players;
    int *alive;
    int curr;
    int n_players;
    int completed;
};

struct player {
  int start;
  int color;
  int n;
};

struct explosion {
    pos from;
    pos to;
    int player;
    int completed;
};
void write_box(box *b,int row,int col,int max,pos *p,int *index);
layout *alloc_layout(int rows,int cols);
void print_layout(layout *l);
void print_atoms(layout *l);
void dealloc_layout(layout *l);
void dealloc_box(box *b);
void dealloc_player(player *p);
state *alloc_state(int,int,player *players,int size);
void dealloc_state(state *s);
player *alloc_player(int color);
int step(state *s);
int add(state *s,int i,int j,int player,int force);
void continue_game(state *s);
void complete(state *s);
void update(state *s,int,int);
void write_player(player *p,int);
#endif