//-------------------- box --------------------


#include "box.h"

box::box(const int& id, const int& x,const int& y,display_manager *d1):
id(id) , location(new coordinates(x,y) ) ,displayer(d1) {
  com.x = x+ 25,com.y = y+25; // set the com for rotation
  // construct with id and location coordinates and display_manager
  color.r =0;
  color.g =0;
  color.b =0;

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
  for ( receive_results*  rr: event_queue ) { // its like  for i in list
    processed =false;                                  //in python
    received(rr); // send the pointer to the received event
    /* when something has come in then call receive which for now
     only adds the value of no of atoms in the box and checks it it max
     and if overflow then call explode
    */
  }
  event_queue = {}; // done with process_events so clear the queue
  return processed;
}

//----------------------------------------------------------------------

void box::received(receive_results* rr) { // the received function
  if (rr) {
     if (owner!=rr->owner) {
       if(owner)
        owner->holding--;
    owner = rr->owner;
    color = owner->color;
    owner->holding++;
    displayer->check =true;
  }

    delete rr;
  }
  if (holding == max) {
    holding =0;
    owner->holding--;
    explode(rr);  // check if the box already has the maximum number of atoms
  }
  else {
    holding+=1; // otherwise just add 1 to holding value
  }
  //displayer->printall();

}

//----------------------------------------------------------------------

void box::explode(receive_results *rr) {
   for( box* b : surrounding) {
     animation *a1  = new animation(b,this,displayer,owner);
     //make a new animation from this box to that surrounding box1

     displayer->current.insert(a1);
   }
   color.r=color.g=color.b=0;
   owner = nullptr;
}

//----------------------------------------------------------------------

box::~box() {
  delete location;
}
