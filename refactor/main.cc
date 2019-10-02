#include "main.h"
int main() {
   state s(10,10);
   s.print();
   s.add(0,0,1);
   s.add(0,0,1);
   s.step();
   s.add(1,0,1);
   s.add(1,1,1);
   s.add(1,1,1);
   s.step();
   s.print();
   s.add(1,0,1);
   s.step();
   s.step();
   s.step();
   s.add(0,1,1);
   s.print();
   s.add(1,1,2);
   s.step();
   s.step();
   s.step();
   s.step();
   s.print();
}