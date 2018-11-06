#ifndef game_base_header
#define game_base_header 1

#include "main.h"

class player {
public:
  player(const string&,const SDL_Color&) ;
  bool compare_owner(box*);
  void add_box(box*);
public:
  SDL_Color *color = nullptr;
  int holding;
public:
  string name;
  player *next =nullptr;
  player *previous = nullptr;
};

class game_base {
public:
  game_base(const vector<player*>&,display_manager*);
  void user_event(const int&);
  void check_holding(player*,vector<player*>&);
  void shrink(player*);
  bool cycle();
  void update();

  display_manager *connection = nullptr;
  int player_cnt;
  int current_cnt;
  player **current = nullptr;
};

#endif
