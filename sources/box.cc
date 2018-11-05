//-------------------- box --------------------


#include "box.h"

box::box(const int& id, const SDL_Rect& location,display_manager *d1):
displayer(d1),owner(nullptr),
location_id(id),
 location(new SDL_Rect(location)),
 color(nullptr)  {


}

//----------------------------------------------------------------------

bool box::update() {
  if (rotation >= 360) {
    rotation = 2;
  }
  else {
    rotation+=2;
  }
return process_events();
}

//----------------------------------------------------------------------

bool box::process_events() {
  bool processed = true; //variable to check if no events are left
  for ( animation*  a: event_queue ) { // its like  for i in list
    processed =false;                                 //in python
    received(a); // send the pointer to the received event
    /* when something has come in then call receive which for now
     only adds the value of no of atoms in the box and checks it it max
     and if overflow then call explode
    */
  }
  event_queue = {}; // done with process_events so clear the queue
  return processed;
}

//----------------------------------------------------------------------

void box::received(animation* a) { // the received function
  if (a) {
     if (owner!=a->owner) {
       if(owner)
        owner->holding--;
    owner = a->owner;
    color = owner->color;
    owner->holding++;
    displayer->check =true;
  }

    displayer->delete_event.insert(a);
    displayer->delete_req=true;
  }
  if (holding == max) {
    holding =0;
    owner->holding--;
    explode();  // check if the box already has the maximum number of atoms
  }
  else {
    holding+=1; // otherwise just add 1 to holding value
  }
  //displayer->printall();

}

//----------------------------------------------------------------------

void box::explode() {
   for( box* b : surrounding) {
     animation *a1  = new animation(b,this,displayer);
     //make a new animation from this box to that surrounding box1

     displayer->current.insert(a1);
   }
   color = nullptr;
   owner = nullptr;
}

//----------------------------------------------------------------------

box::~box() {
  delete location;
}
