#ifndef box_header
#define box_header 1

#include "main.h"

enum  type { // these are just constants to make it easier to
    TOP=1,    // identify what is what
    BOTTOM=2,
    LEFT=3,
    RIGHT=4,
    MIDDLE=5,
    TOPRC=6,
    TOPLC=7,
    BOTTOMRC=8,
    BOTTOMLC=9
};

class box {
public:
  box(const int&,const int&,const int&,display_manager*); //constructor for box

  //color of the ball
  int id ;    //id of the box
  coordinates *location;    //pointer to location of this box


 /* basically if balls comes in and touches here then receive event queue
  add up
  */

  set<receive_results*> event_queue; //a queue for when some ball has touched the com
  int max ;  //the maximum
  int holding =0; //the no it hold right now

  display_manager *displayer = nullptr; // has everything to output graphics
  bool process_events(); //iterate through all events and tell if it it did something
  void explode(receive_results*);  // when it overflows
  void received(receive_results*);
  bool update();
  void reset_color();
  set<box*> surrounding; //pointers to surrounding boxes
  int type; //the type of the box;
  player *owner = nullptr;
  ~box();
public: // rotation and com
  double rotation = 0.0;
  SDL_Point com;
  SDL_Color color;
};

#endif
