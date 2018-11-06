//-------------------- player --------------------


#include "player.h"

player::player(const int& r,const int& g,const int& b,game_base* d):connection(d),color(new SDL_Color()) {
color->r=r;
color->g=g;
color->b=b;
}

//----------------------------------------------------------------------

bool player::compare_owner(box* b_check) {
  bool ret =true;
  if (!b_check->owner){ //if it doesnt have a owner
    add_box(b_check);
  }
  else {
    //if there is a owner and check if it tis the same owner

    if (b_check->owner!=this) {
      ret = false;
    }
  }
  return ret;
}

//----------------------------------------------------------------------

void player::add_box(box* b){
  b->owner = this;
  b->color =color;
  holding++; //add to holding
}
