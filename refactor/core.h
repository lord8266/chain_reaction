#ifndef core_
#define core_
#include "main.h"

struct pos {
   pos(int row,int col):row(row),col(col) {}
   int row;
   int col;
};
class box {
   public:
      box(layout &board,int row,int col,vector<pos> p):board(board),neighbours(p),player(0),row(row),col(col),atoms(0),max(neighbours.size()-1) {}
      
   private:
      layout &board;
      
   public:
      vector<pos> neighbours;
      int player;
      int row;
      int col;
      int atoms;
      int max;
};

class layout {

public:
   layout(int rows,int cols);
   void print();
   void bind();
public:
   int rows;
   int cols;
   vector<vector<box>> boxes; 
};

class state {

   public:
      state(int row,int col);
      bool add(int row,int col,int player=0,bool force=false);
      void print();
      bool step();
   private:
      layout board;
      vector<explosion> ongoing;
};

class explosion {
   public:
      explosion(pos f,pos t,int p):from(f),to(t),player(p) {}
      int get_status() { return 1;}
      pos from;
      pos to;
      int player;
};

#endif