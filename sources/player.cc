//-------------------- player --------------------


#include "player.h"

player::player(const int& r,const int& g,const int& b,game_base* d):connection(d),color(new SDL_Color()) {
color->r=r;
color->g=g;
color->b=b;
}

//----------------------------------------------------------------------

bool player::compare_color(box* b_check) {
  bool ret = false;
  SDL_Color *c_check = b_check->color;
  if (!c_check){
    b_check->owner = this;
    b_check->color = color;
    holding++;
    ret =true;
  }
  else {
    if ((c_check->r==color->r) && (c_check->g==color->g) && (c_check->b==color->b)) {

      ret = true;
    }
    else {
      ret = false;
    }
  }
  return ret;
}

//----------------------------------------------------------------------
