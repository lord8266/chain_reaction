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
  friend class player;
  friend class display_manager;
  friend class animation;
public:
  box(const int&,const SDL_Rect&,display_manager*); //constructor for box
  bool process_events(); //iterate through all events and tell if it it did something
  void explode();  // when it overflows
  void received(animation*);
  bool update();
  void reset_color();
  ~box();

private:
  display_manager *displayer = nullptr;
  set<animation*> event_queue;
  set<box*> surrounding;
  player *owner = nullptr;
  int location_id;
private:
  int max ;  //the maximum
  int holding =0; //the no it hold right now
  int type; //the type of the box;

private: // rotation and com
  double rotation = 0.0;
  SDL_Rect *location=nullptr;
  SDL_Color *color;

};

#endif
