#ifndef animation_header
#define animation_header 1

#include "main.h"



class animation {
  friend class box;
public:
  animation(box*,box*,display_manager*);
  void run();              // run the animation
  void completion_event();  //if completed then put it on the recieve queue of the box
  void update();              //update location of the ball
  void render(); //render the animation
  void set_direction(); // function to set the direction of animation
  // it is automatically deduced from the two boxes
  int speed=4;
private:
  display_manager *connection = nullptr; //pointer to the displayer
  player *owner =nullptr;
private:
  box *to =nullptr; // the coordinates to which ball must go
  box *from =nullptr; //coordinates from which ball has orignated
  SDL_Rect *current = nullptr; // the current location of the ball
  SDL_Rect *destination = nullptr;
  SDL_Point *direction =nullptr;
  SDL_Color *color = nullptr;
private:
  bool running = false;
};

#endif
