#ifndef display_manager_header
#define display_manager_header 1

#include "main.h"

class display_manager {
public:
  display_manager(); //constructor for display_manager
  map<int,box*> boxes ; //map to all the boxes to their ids it is like dict in python

  set<animation*> current; // the current animations going on
  set<animation*> delete_event;
  void add_animation(box* to,box* from); // balls goes to where from where
  // when box explodes this is called to add animation
  void run() ; //run the game loop
  bool update(); // update events and check if nothing new has happened
  void printall();
  void process_pending(); // function to run all animations before doing next task
  void print_location();
  void render(); //render graphics
  void process_events();
  void draw_grid(); // function to draw the grid as of now is 500x500 grid
  void make_textures(); // make textures for rendering
  void make_atoms();
  void user_event(const int&); // when the user clicks send the event
  void color_change(const int&); //utility function to revert back to the previously used color
  void texture_mod(const int&,const int&);  // changes the color mod of the texture
  void run_check();
  void render_atom_count(); // renders the no of atoms in each box
  void set_surrounding(); // it is function to the surrounding elements
  void set_type(); // a function to set the type of the box
  bool running = false ; // boolean to hold if any animation is running
  bool deleted = false;
  bool delete_req = false;
  bool check = false;
  void setup(); // function to initialize the sdl side
  void quit(); // a function to quit everything
  void remove_animation(animation*);
  ~display_manager();
public:
  SDL_Window *w1 = nullptr; // window pointer
  SDL_Renderer * w_ren =nullptr; //pointer to renderer
  map<int,SDL_Texture*> value_maps; // textures to hold numbers to display
  SDL_Rect r_text; // rectangle for holding the location to render text
  event_manager *e1 = nullptr; // class to handle all types events
  bool main_running = false;
  SDL_Color grid_color;
public:
  game_base *game_control =nullptr;
};

#endif