//-------------------- game_base --------------------


#include "game_base.h"

game_base::game_base(display_manager* d):connection(d),player_cnt(3),current_cnt(-1) { // enter the game from -1
  players.push_back(new player(255,0,0,this));
  players.push_back(new player(0,255,0,this));
  players.push_back(new player(0,0,255,this));
  cycle();
}

//----------------------------------------------------------------------

void game_base::update() {
  int r =0,g=0,b=0;
  for (player* p1 : players) {
    r = p1->color->r;
    g=p1->color->g;
    b=p1->color->b;
    cout<<"( "<<r<<" "<<g<<" "<<b<<" ): "<<p1->holding<<"\n";
  }
  cout<<endl;
}

//----------------------------------------------------------------------

void game_base::cycle() {
  if (current_cnt==player_cnt-1){
    current_cnt =0;
    current = players[current_cnt];
  }
  else {
    current_cnt++;
    current = players[current_cnt];
  }
  connection->grid_color = current->color;
}

//----------------------------------------------------------------------

void game_base::user_event(const int& i) {
  box* temp_b = &connection->boxes[i];

  if(current->compare_color(temp_b)) {
  temp_b->received(nullptr);
  cycle();
  }

}

//----------------------------------------------------------------------
