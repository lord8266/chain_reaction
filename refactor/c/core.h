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
};

 struct layout {

   int rows;
   int cols;
   box *boxes; 
};

 struct state {
    layout board;
    list ongoing;
};

struct explosion {
    pos from;
    pos to;
    int player;
};

#endif