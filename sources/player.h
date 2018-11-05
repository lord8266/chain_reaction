#ifndef player_header
#define player_header 1

#include "main.h"

class player {
public:
  player(const int&,const int&,const int&,game_base*);
  bool compare_color(box*);
  void update() { holding++;}
  game_base *connection =nullptr;
  SDL_Color *color=nullptr;
  int holding=0;
};

#endif
