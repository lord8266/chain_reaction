#ifndef event_manager_header
#define event_manager_header 1

#include "main.h"

class event_manager {
public:
  event_manager(display_manager*);
  void check_events(SDL_Event *);
  void handle_click();
  display_manager *connection =nullptr;
  int x,y;
};

#endif