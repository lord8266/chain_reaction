#ifndef coordinates_header
#define coordinates_header 1

#include "main.h"

class coordinates { //coordinates class
public:
  coordinates(const int& x,const int& y):x(x) ,y(y) { }
  coordinates( box*); // copy constructor
  int x; //x
  int y; //y
};

#endif