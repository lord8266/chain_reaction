#ifndef player_header
#define player_header 1

#include "main.h"

class player {
public:
  player(const int&,const int&,const int&,game_base*);
  bool compare_color(box*);
  void update() { holding++;}
  SDL_Color color;
  game_base *connection =nullptr;
  int holding=0;
};

#endif