#ifndef game_base_header
#define game_base_header 1

#include "main.h"

class game_base {
public:
  game_base(display_manager*);
  void user_event(const int&);
  void cycle();
  void update();
  vector<player*> players;
  display_manager *connection = nullptr;
  player *current = nullptr;
  int player_cnt;
  int current_cnt;
};

#endif