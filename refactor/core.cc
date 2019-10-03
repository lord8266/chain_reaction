#include "core.h"

vector<pos> neighbours(int i,int j,int rows,int cols) {
   vector<pos> v;
      
   if (i>0) {
      v.emplace_back(i-1,j) ;
   }
   if (i<(rows-1)) {
      v.emplace_back(i+1,j);
   }
   if (j<(cols-1)) {
      v.emplace_back(i,j+1);
   }
   if (j>0) {
      v.emplace_back(i,j-1);
   }
   return v;
}

layout::layout(int rows,int cols):rows(rows),cols(cols) {
   for (int i=0;i<rows;i++) {
      boxes.push_back({});
      for (int j=0;j<cols;j++) {
         boxes[i].push_back(box(*this,i,j,neighbours(i,j,rows,cols)));
      }
   }
}

void layout::print() {
   for (auto i : boxes) {
      for (auto j: i) {
         printf("(%d, %d)-> ",j.row,j.col);
         for (auto k: j.neighbours) {
            printf("(%d, %d) ",k.row,k.col);
         }
         cout<<endl;
      }
      cout<<endl;
   }
}

state::state(int rows,int cols):board(layout(rows,cols)) {}

bool state::add(int i,int j,int player,bool force) {
   if (!force && !(board.boxes[i][j].player==player || board.boxes[i][j].player==0)) {
         cout<<"here"<<endl;
         return false;
      }
   box &b = board.boxes[i][j]; 
   
   if (b.atoms==b.max){
      b.atoms =0;
      
      for (auto n:b.neighbours) {
         ongoing.emplace_back(pos(b.row,b.col),pos(n.row,n.col),b.player);
         
      }
      b.player =0;
   }
   else {
      b.player = player;
      b.atoms++;
   }
   return true;
}

bool state::step() {
   vector<explosion> a;
   vector<int> b;
   cout<<ongoing.size()<<endl;
   for (size_t i=0;i<ongoing.size();i++) {
      
      explosion e = ongoing[i];
      cout<<"i arrived"<<e.to.row<<" "<<e.to.col<<endl;
      if (e.get_status()==1) {
         a.push_back(e);
         b.push_back(i);
      }
   }
   for (auto i: b) {
      ongoing.erase(ongoing.begin()+i);
   }
   for (auto p :a) {
      add(p.to.row,p.to.col,p.player);
   }
   return ongoing.size();
}

void state::print() {
   for (auto i:board.boxes) {
      for (auto j:i) {
         cout<<j.atoms<<" ";
      }
      cout<<endl;
   }
   cout<<endl;
}

void state::complete() {
   while(step());
}


