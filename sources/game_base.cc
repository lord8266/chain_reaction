//-------------------- game_base --------------------


#include "game_base.h"

game_base::game_base(const vector<player*> &data_vec,display_manager* d):connection(d),player_cnt(3),current_cnt(-1),
current(new player*()) { // enter the game from -1

  auto a = data_vec.begin();
  (*a)->next = *(a+1);
  (*a)->previous = *(data_vec.end()-1);
 a++;
  for (;a!=data_vec.end()-1;a++) {
    (*a)->next = *(a+1);
    (*a)->previous = *(a-1);
  }
  (*a)->next = *data_vec.begin();
  (*a)->previous = *(a-1);

  *current = *data_vec.begin();
  connection->grid_color = (*current)->color;
}

//----------------------------------------------------------------------

player::player(const string&s,const SDL_Color& c):
color(new SDL_Color(c)),name(s) {
}
//----------------------------------------------------------------------

void game_base::update() {
  player *start = *current;
  vector<player*> shrink_list;
  cout<<start->color<<" "<<start->holding<<endl;
  check_holding(start,shrink_list);
  start = start->next;
  while(start!=(*current)) {
    cout<<start->color<<" "<<start->holding<<endl;
    check_holding(start,shrink_list);
    start = start->next;
  }
  for (player* p: shrink_list) {
    shrink(p);
  }
  cout<<endl;
  while(!(*current)->holding) {
    *current = (*current)->next;
  }
  connection->grid_color = (*current)->color;
  if((*current)->next==*current) {
    connection->end_texture_create();
    connection->end_displaying = true;
    //connection->main_running =false;
  }
}

void game_base::check_holding(player *p,vector<player*> &shrink_list) {

  if(!p->holding) {
    shrink_list.push_back(p);
  }

}

void game_base::shrink(player* p) {
  p->previous->next = p->next;
  p->next->previous=p->previous;
}



//----------------------------------------------------------------------

void game_base::user_event(const int& i) {
  box* temp_b = &connection->boxes[i];

  if((*current)->compare_owner(temp_b)) {
    //if compare owner was fine then send the received event

  temp_b->received(nullptr);
  cycle();
  }

}

//----------------------------------------------------------------------

bool game_base::cycle() {

  *current = (*current)->next;

  connection->grid_color = (*current)->color;

  return true;
}

//----------------------------------------------------------------------

bool player::compare_owner(box* b_check) {
  bool ret =true;
  if (!b_check->owner){ //if it doesnt have a owner
    add_box(b_check);
  }
  else {
    //if there is a owner and check if it tis the same owner

    if (b_check->owner!=this) {
      ret = false;
    }
  }
  return ret;
}

//----------------------------------------------------------------------

void player::add_box(box* b){
  b->owner = this;
  b->color =color;
  holding++; //add to holding
}
