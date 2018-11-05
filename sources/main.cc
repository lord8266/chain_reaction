#include "main.h"

//int animation::speed = 4;
int main() {
  SDL_Rect r1;
  r1.x = 10;
  r1.y=7;
  r1.w=50;
  r1.h=50;
  display_manager d1(r1);
  d1.run();
}
