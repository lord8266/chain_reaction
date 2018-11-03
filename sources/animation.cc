//-------------------- animation --------------------


#include "animation.h"

animation::animation(box* to ,box* from,display_manager* displayer,player* owner)
:  connection(displayer),to(to) ,from(from),current(new coordinates(from)) ,owner(owner)
 // construct to pointer and from pointer
{
set_direction(); //set direction for animation
rectangle.x = current->x; // set x coordinate
rectangle.y = current->y; // set y cooridnate
rectangle.w=rectangle.h=50;//set widht and height as 50;
/*color.r= from->color.r;
color.g = from->color.g; //set the colors
color.b = from->color.b; //for now
color.a =255;*/
}

//----------------------------------------------------------------------

void animation::completion_event() { // when the ball has reached the com of target

  receive_results * rec_temp = new receive_results(to,from,owner); // make a new receive_results
  to->event_queue.insert(rec_temp); // put it on the event queue
  //connection->current.erase(this); // remove it form the current queue animation
  connection->delete_req = true;
  connection->delete_event.insert(this);

}

//----------------------------------------------------------------------

void animation::render() {
  connection->texture_mod(1,0);
  SDL_SetTextureColorMod(connection->value_maps[1],owner->color.r,owner->color.g,owner->color.b);
  SDL_RenderCopy(connection->w_ren,connection->value_maps[1],nullptr,&rectangle);
  connection->texture_mod(1,1);
}

//----------------------------------------------------------------------

void animation::set_direction() { //function which sets the direction
   coordinates *fromc = from->location,*toc = to->location;
   // retrieve locations of two coordinates;

   if (toc->x == fromc->x) { // same x coordinate or same column

       if (toc->y > fromc->y) { // if two is is the right of
         direction = DOWNWARD; // set direction forward
       }
       else { // it is on the left
         direction = UPWARD; // set direction backward
       }
   }
   else if(toc->y == fromc->y) { // same y coordinate or same row

       if (toc->x > fromc->x) { // if below from
         direction = RIGHT;

       }
       else { // above from
        direction =LEFT;
       }
   }
   else {
     /* if nothing is equal something is wrong
      so throw an error
      */
      throw std::runtime_error("direction1");
       // throw error with message
   }
}

//----------------------------------------------------------------------

void animation::update() { //updating the animation
  /*
  with the direction variable only one coordinate has to be satisfied
  to say that the ball has reached and then end the animation and update the
  box events for
  */

  bool condition = false; // check if x coordinate has reached

 switch (direction) { // switch the direction variable
  case UPWARD: // it is going up need to check y coordinate
       current->y-=speed; // subtract y
       condition = current->y<=to->location->y; // check if it above to box
   break;

   case DOWNWARD:
    current->y+=speed; // now to is below from
    condition = current->y>=to->location->y;
    break;

  case LEFTWARD:
  current->x-=speed; // now check for the x coordinate
  condition = current->x<=to->location->x;
  break;

  case RIGHTWARD:
  current->x+=speed; // now to box is on the
  condition = current->x>=to->location->x; // right of from box
  break;

  default:
  // if none is satisfied throw error
  throw std::runtime_error("update check1"); // throw error with message

 }
  rectangle.x = current->x;
  rectangle.y = current->y;
//  cout<< current->x << " " << current->y<<endl;
  if (condition)
    completion_event(); // for now completion_event is called
}

//----------------------------------------------------------------------

void animation::run() { // run the animation
  update(); // update the animation
  render(); // render the animation
  // for now just call update
}

//----------------------------------------------------------------------

