//-------------------- animation --------------------


#include "animation.h"

animation::animation(box* to ,box* from,display_manager* displayer)
:  connection(displayer),
owner(from->owner),
to(to) ,from(from),
current(new SDL_Rect(*from->location)),
destination(to->location),
direction(new SDL_Point()),
color(owner->color),
running(true)

 // construct to pointer and from pointer
{
set_direction();
}

//----------------------------------------------------------------------

void animation::completion_event() { // when the ball has reached the com of target


  to->event_queue.insert(this); // put it on the event queue
  //connection->current.erase(this); // remove it form the current queue animation
 running=false;
}

//----------------------------------------------------------------------

void animation::render() {
  connection->texture_mod(1,0);
  SDL_SetTextureColorMod(connection->value_maps[1],owner->color->r,owner->color->g,owner->color->b);
  SDL_RenderCopy(connection->w_ren,connection->value_maps[1],nullptr,current);
  connection->texture_mod(1,1);
}

//----------------------------------------------------------------------

void animation::set_direction() { //function which sets the direction
   direction->x = destination->x - current->x;
   direction->y = destination->y - current->y;
   direction->x/=destination->w;
   direction->y/=destination->h;
}

//----------------------------------------------------------------------

void animation::update() { //updating the animation
  /*
  with the direction variable only one coordinate has to be satisfied
  to say that the ball has reached and then end the animation and update the
  box events for
  */

  current->x +=direction->x*speed;
  current->y +=direction->y*speed;

  int dot1 = current->x*direction->x + current->y*direction->y;
  int dot2 = destination->y*direction->y + destination->x*direction->x;

  if (dot1>dot2)
    completion_event(); // for now completion_event is called
}

//----------------------------------------------------------------------

void animation::run() { // run the animation
  if(running) {
  update(); // update the animation
  render(); // render the animation
  // for now just call update
}
}

//----------------------------- coordinates -----------------------------------------
