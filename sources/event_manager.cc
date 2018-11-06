//-------------------- event_manager --------------------


#include "event_manager.h"

event_manager::event_manager(display_manager* d):connection(d),x(0),y(0) {

}

//----------------------------------------------------------------------

void event_manager::check_events(SDL_Event* e) {
   // make a new event
  while(SDL_PollEvent(e)) { //poll through all pending events
    switch (e->type) { // check type of the event
      case SDL_QUIT:
        connection->quit(); // close the program
        break;
      case SDL_MOUSEBUTTONDOWN:
        handle_click();
        break;
    }
  }

}

//----------------------------------------------------------------------

void event_manager::handle_click() {
  SDL_GetMouseState(&x,&y); // get mouse location


  x = x/connection->game_details->w;
  y = y/connection->game_details->h; 
  //convert into rows and cols of the allocated array

  connection->user_event(x+connection->game_details->x*y); // generate id and send the event
}

//----------------------------------------------------------------------
