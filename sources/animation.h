#ifndef animation_header
#define animation_header 1

#include "main.h"

class animation {
public:
  enum direction { // enumeration for direction of animation
    DOWNWARD= 1,
    UPWARD=2,
    LEFTWARD=3,
    RIGHTWARD=4,
  };
  animation(box*,box*,display_manager*,player*);
  display_manager *connection = nullptr; //pointer to the displayer
  void run();              // run the animation
  void completion_event();  //if completed then put it on the recieve queue of the box
  box *to =nullptr; // the coordinates to which ball must go
  box *from =nullptr; //coordinates from which ball has orignated
  void update();              //update location of the ball
  coordinates *current = nullptr; // the current location of the ball
  void render(); //render the animation
  int direction = 0; // holds the direction value
  void set_direction(); // function to set the direction of animation
  // it is automatically deduced from the two boxes
  SDL_Rect rectangle ;// as of now rendering rectangle
  static int speed;
  player* owner = nullptr;
};

#endif