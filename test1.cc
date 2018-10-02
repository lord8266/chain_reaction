/*

if overflow then manually handle direction of balls

have a receive event which then will increase count


*/

#include "header.h" //includes all necessary libararies
#include <SDL.h>
#include <SDL_ttf.h>
#include <SDL_image.h>


class display_manager;
class animation;
class receive_results;
class player;
class box;
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
class player {
public:
  player(const int&,const int&,const int&,game_base*);
  bool compare_color(box*);
  void update() { holding++;}
  SDL_Color color;
  game_base *connection =nullptr;
  int holding=0;
};

class box;
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

class receive_results {
public:
  receive_results(box* to,box* from,player*);
  box* to =nullptr; // to where ball is coming
  box* from =nullptr;  // from where ball has come
  player* owner = nullptr;
};

class coordinates { //coordinates class
public:
  coordinates(const int& x,const int& y):x(x) ,y(y) { }
  coordinates( box*); // copy constructor
  int x; //x
  int y; //y
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
class event_manager;
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

class event_manager {
public:
  event_manager(display_manager*);
  void check_events(SDL_Event *);
  void handle_click();
  display_manager *connection =nullptr;
  int x,y;
};

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

int animation::speed = 4;
// =---------------------------  start of constructor defenitions --------------

receive_results::receive_results(box * to,box* from,player* owner):to(to),from(from),owner(owner) {

}
game_base::game_base(display_manager* d):connection(d),player_cnt(3),current_cnt(-1) { // enter the game from -1
  players.push_back(new player(255,0,0,this));
  players.push_back(new player(0,255,0,this));
  players.push_back(new player(0,0,255,this));
  cycle();
}

player::player(const int& r,const int& g,const int& b,game_base* d):connection(d) {
  color.r =r;
  color.g = g;
  color.b =b;

}



display_manager::display_manager():boxes(),current(),e1(new event_manager(this)),game_control(new game_base(this)) { //initalize both sets to nothing
                                                    //set is the same as in python
                                                    // make a event handler to handle events

  for (int i=1;i<=5;i++) { // for each row

    for (int j=1;j<=5;j++) { // for each column

       /*make a new box with id and coordinates
        id is basically the box number starting from
        1 and goes to 100
        each box is a square of 50x50 width
        so center of mass will start form 25,-25
       */
      int id = i + (j-1)*5;
      box* temp = new box( id,  25+(i-1)*100   ,  25+(j-1)*(100)  ,   this  );

      //      id    , x coordinate ,y cooridinate , pointer to displayer
// the +25 is for shift of coordinates just try it out yourself how you would do it
      //  apparently gaming engines use the fourth quadrant
      //  hence the negative sign on j


      boxes.insert({id,temp}); // insert the newly created box into the boxes - set
                              // like a dictionary from id to box
}

  }
  set_type(); // sets the type and maximum of each box
  set_surrounding(); // sets the surrounding boxes of each box
  setup(); // setup the SDL side
  color_change(0);
  main_running =true;
}

box::~box() {
  delete location;
}
display_manager::~display_manager() {
  for (auto a : boxes) {
    delete a.second;
  }
  for (auto a: value_maps) {
    SDL_DestroyTexture(a.second);
  }
  SDL_DestroyRenderer(w_ren);
  SDL_DestroyWindow(w1);
  SDL_Quit();
}
event_manager::event_manager(display_manager* d):connection(d),x(0),y(0) {

}
box::box(const int& id, const int& x,const int& y,display_manager *d1):
id(id) , location(new coordinates(x,y) ) ,displayer(d1) {
  com.x = x+ 25,com.y = y+25; // set the com for rotation
  // construct with id and location coordinates and display_manager
  color.r =0;
  color.g =0;
  color.b =0;

}

animation::animation(box* to ,box* from,display_manager* displayer,player* owner)
:  connection(displayer),to(to) ,from(from),current(new coordinates(from)) ,owner(owner)
 // construct to pointer and from pointer
{
set_direction(); //set direction for animation
rectangle.x = current->x; // set x coordinate
rectangle.y = current->y; // set y cooridnate
rectangle.w=rectangle.h=50;//set widht and height as 50;
/*color.r= from->color.r;
color.g = from->color.g; //set the colors
color.b = from->color.b; //for now
color.a =255;*/
}

coordinates::coordinates( box* c1) {
  x = c1->location->x;
  y=c1->location->y;
}


// ------------- start of member functions defintions ---------------

void game_base::update() {
  int r =0,g=0,b=0;
  for (player* p1 : players) {
    r = p1->color.r;
    g=p1->color.g;
    b=p1->color.b;
    cout<<"( "<<r<<" "<<g<<" "<<b<<" ): "<<p1->holding<<"\n";
  }
  cout<<endl;
}
void display_manager::run_check() {

    check = false;
game_control->update();

}
bool player::compare_color(box* b_check) {
  bool ret = false;
  SDL_Color c_check = b_check->color;
  if ((c_check.r==0) && (c_check.g==0) && (c_check.b==0)){
    b_check->owner = this;
    b_check->color = color;
    holding++;
    ret =true;
  }
  else {
    if ((c_check.r==color.r) && (c_check.g==color.g) && (c_check.b==color.b)) {

      ret = true;
    }
    else {
      ret = false;
    }
  }
  return ret;
}
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

void game_base::user_event(const int& i) {
  box* temp_b = connection->boxes[i];

  if(current->compare_color(temp_b)) {
  temp_b->received(nullptr);
  cycle();
  }

}

void display_manager::remove_animation(animation* a_d) {
  current.erase(a_d);
  delete a_d;
}
void event_manager::check_events(SDL_Event* e) {
   // make a new event
  while(SDL_PollEvent(e)) { //poll through all pending events
    switch (e->type) { // check type of the event
      case SDL_QUIT:
        connection->quit(); // close the program
        break;
      case SDL_MOUSEBUTTONDOWN:
        handle_click();
        break;
    }
  }

}

void event_manager::handle_click() {
  SDL_GetMouseState(&x,&y); // get mouse location

  if (x > 500|| y>=500) {
    return;
  }
  x = x/100+1; // convert cooridnates to 5,5 range
  y = y/100;

  connection->user_event(x+5*y); // generate id and send the event
}

void display_manager::process_events() {
  SDL_Event e;
  while(SDL_PollEvent(&e)) {

    switch(e.type) {
      case SDL_QUIT:
      quit();
      break;
      case SDL_MOUSEBUTTONDOWN:
      if(running){
       e1->handle_click();
     }
      break;

  }
}
}

void display_manager::quit(){
  //SDL_Quit();
  //cout<<"here"<<endl;
  main_running = false;

}
void display_manager::color_change(const int& i) { //function to change color
  // have to call(0) brefor calling(1)
  static Uint8 r,g,b,a; // static values cause need to store them
  if(i) { // if i need to revert back to the previous color being used
      SDL_SetRenderDrawColor(w_ren,r,g,b,a); // set the colors
  }
  else {
    SDL_GetRenderDrawColor(w_ren,&r,&g,&b,&a); //get the colors to rgba
  }
}

void display_manager::texture_mod(const int& tex_index,const int& i) {
  static Uint8 r,g,b; // static values cause need to store them
  if(i) { // if i need to revert back to the previous color being used
      SDL_SetTextureColorMod(value_maps[tex_index],r,g,b); // set the colors
  }
  else {
    SDL_GetTextureColorMod(value_maps[tex_index],&r,&g,&b); //get the colors to rgba
  }
}

void display_manager::draw_grid() {
  color_change(0);
  if(!running) { // running is false when animation is going on
   SDL_SetRenderDrawColor(w_ren,255,255,255,255);
  }
  else {

  SDL_SetRenderDrawColor(w_ren,grid_color.r,grid_color.g,grid_color.b,255);
}
  for (int i=0;i<500;i+=100) {
    SDL_RenderDrawLine(w_ren,0,i,500,i);
  }
  SDL_RenderDrawLine(w_ren,0,499,500,499);
  for (int i=0;i<500;i+=100) {
    SDL_RenderDrawLine(w_ren,i,0,i,500);
  }
  SDL_RenderDrawLine(w_ren,499,0,499,500);
  color_change(1);
}

void display_manager::user_event(const int& i) { // user event
  //process_pending();
  // go through all animations before doing anything
  game_control->user_event(i);
  /* if user clicks on a box then send an event to the corresponding box
     since im now sending a nullptr the box would identify that it is a user event
     and im using the same flow as before
     */

}

void display_manager::setup() {
  SDL_Init(SDL_INIT_VIDEO);
  w1 = SDL_CreateWindow("test",640,480,500,500,SDL_WINDOW_SHOWN);
  w_ren = SDL_CreateRenderer(w1,-1,SDL_RENDERER_ACCELERATED| SDL_RENDERER_PRESENTVSYNC);
  //make_textures(); // make all textures need to display on
  make_atoms();
  r_text.w=50;
  r_text.h = 50;
}

void display_manager::make_atoms() {
  IMG_Init(IMG_INIT_PNG);
  SDL_Surface *s_temp = IMG_Load("img/a1.png");
  SDL_Texture *t1  = SDL_CreateTextureFromSurface(w_ren,s_temp);
  value_maps.insert({1,t1});
  SDL_FreeSurface(s_temp);

  s_temp = IMG_Load("img/a2.png");
  t1  = SDL_CreateTextureFromSurface(w_ren,s_temp);
  value_maps.insert({2,t1});
  SDL_FreeSurface(s_temp);

  s_temp = IMG_Load("img/a3.png");
  t1  = SDL_CreateTextureFromSurface(w_ren,s_temp);
  value_maps.insert({3,t1});
  SDL_FreeSurface(s_temp);
 IMG_Quit();

}

void display_manager::render_atom_count() {
  box *temp = nullptr; // set the bopx operating on
  int holding =0;
  for (int i=1;i<=25;i++) { // go in range of boxes
    temp = boxes[i];
    holding = temp->holding;


    if (holding) {
      texture_mod(holding,0);
      SDL_SetTextureColorMod(value_maps[holding],temp->color.r,temp->color.g,temp->color.b);
      if (holding==1) {
        r_text.w=50;
        r_text.h =50;
        r_text.x = temp->location->x;
        r_text.y = temp->location->y;
      }
      else{
        r_text.w=80;
        r_text.h =80;
        r_text.x = temp->location->x-10;
        r_text.y = temp->location->y-10;
}

SDL_RenderCopyEx(w_ren,value_maps[holding],nullptr,&r_text,temp->rotation,nullptr,SDL_FLIP_NONE);
texture_mod(holding,1);
}
  }
}
void display_manager::make_textures() {
  /*
  as of now this makes textures 1 2 3 for
  displaying the count of atoms in the
  box
  */

  TTF_Init(); // initialize ttf
  TTF_Font *temp_font = TTF_OpenFont("textures/arial.ttf",28); // take font from arial
  SDL_Color color1{100,0,100,255}; // make a color variable

  SDL_Surface *temp = TTF_RenderText_Solid(temp_font,"0",color1); // render text
  SDL_Texture *temp_texture = SDL_CreateTextureFromSurface(w_ren,temp);
  SDL_FreeSurface(temp);
  value_maps.insert({0,temp_texture});

  temp = TTF_RenderText_Solid(temp_font,"1",color1);
  temp_texture = SDL_CreateTextureFromSurface(w_ren,temp);
  SDL_FreeSurface(temp);
  value_maps.insert({1,temp_texture});

  temp = TTF_RenderText_Solid(temp_font,"2",color1);
  temp_texture = SDL_CreateTextureFromSurface(w_ren,temp);
  SDL_FreeSurface(temp);
  value_maps.insert({2,temp_texture});

  temp = TTF_RenderText_Solid(temp_font,"3",color1);
  temp_texture = SDL_CreateTextureFromSurface(w_ren,temp);
  SDL_FreeSurface(temp);
  value_maps.insert({3,temp_texture});
  TTF_CloseFont(temp_font); // close everything
  TTF_Quit(); // quit ttf

}

void display_manager::print_location() {
  for (int i=1;i<=5;i++ ) {
    for(int j=1 ;j<=5;j++) {


    coordinates *temp = boxes[i+5*(j-1)]->location;
  //  cout<<"( "<<temp->x<< " , "<<temp->y<<" )  ";
  }
  cout<<endl;
  }
}
void animation::completion_event() { // when the ball has reached the com of target

  receive_results * rec_temp = new receive_results(to,from,owner); // make a new receive_results
  to->event_queue.insert(rec_temp); // put it on the event queue
  //connection->current.erase(this); // remove it form the current queue animation
  connection->delete_req = true;
  connection->delete_event.insert(this);

}

void animation::render() {
  connection->texture_mod(1,0);
  SDL_SetTextureColorMod(connection->value_maps[1],owner->color.r,owner->color.g,owner->color.b);
  SDL_RenderCopy(connection->w_ren,connection->value_maps[1],nullptr,&rectangle);
  connection->texture_mod(1,1);
}

void animation::set_direction() { //function which sets the direction
   coordinates *fromc = from->location,*toc = to->location;
   // retrieve locations of two coordinates;

   if (toc->x == fromc->x) { // same x coordinate or same column

       if (toc->y > fromc->y) { // if two is is the right of
         direction = DOWNWARD; // set direction forward
       }
       else { // it is on the left
         direction = UPWARD; // set direction backward
       }
   }
   else if(toc->y == fromc->y) { // same y coordinate or same row

       if (toc->x > fromc->x) { // if below from
         direction = RIGHT;

       }
       else { // above from
        direction =LEFT;
       }
   }
   else {
     /* if nothing is equal something is wrong
      so throw an error
      */
      throw std::runtime_error("direction1");
       // throw error with message
   }
}

void display_manager::process_pending() {
      // till animations isnt zero go on running
     // call run

    while ((!update())||(current.size()!=0)){ // magically does the job of
                                              // processing all events and animations
      run();  // call run
    }
}
void animation::update() { //updating the animation
  /*
  with the direction variable only one coordinate has to be satisfied
  to say that the ball has reached and then end the animation and update the
  box events for
  */

  bool condition = false; // check if x coordinate has reached

 switch (direction) { // switch the direction variable
  case UPWARD: // it is going up need to check y coordinate
       current->y-=speed; // subtract y
       condition = current->y<=to->location->y; // check if it above to box
   break;

   case DOWNWARD:
    current->y+=speed; // now to is below from
    condition = current->y>=to->location->y;
    break;

  case LEFTWARD:
  current->x-=speed; // now check for the x coordinate
  condition = current->x<=to->location->x;
  break;

  case RIGHTWARD:
  current->x+=speed; // now to box is on the
  condition = current->x>=to->location->x; // right of from box
  break;

  default:
  // if none is satisfied throw error
  throw std::runtime_error("update check1"); // throw error with message

 }
  rectangle.x = current->x;
  rectangle.y = current->y;
//  cout<< current->x << " " << current->y<<endl;
  if (condition)
    completion_event(); // for now completion_event is called
}

void animation::run() { // run the animation
  update(); // update the animation
  render(); // render the animation
  // for now just call update
}

void display_manager::run() {
  bool temp_running = false;
  while (main_running) {
    process_events(); // process all events;
    temp_running = update(); //call update
   render(); //call render
   if (check) {
     run_check();
   }
   running = current.size()==0 && temp_running;
}

}

bool display_manager::update() {
  bool updated = true;
  for (pair<int,box*> p_box : boxes ) {
    if(!p_box.second->update())
      updated = false;
  }
  if(delete_req){

  for (animation* d_anim: delete_event) {
    current.erase(d_anim);
    delete d_anim;
  }
  delete_event = {};
  delete_req = false;
}

  return updated;
}

void display_manager::render() {
  SDL_RenderClear(w_ren);
  draw_grid();
  render_atom_count();
  color_change(0);
  SDL_SetRenderDrawColor(w_ren,30,40,50,60);
  for( animation* a_anim: current) {
    a_anim->run();
  }
  color_change(1);
  SDL_RenderPresent(w_ren);
  //cout<<running<<endl;
}

void display_manager::printall() { //printing function
  for (int i=1;i<=25;i++) {

    cout<<boxes[i]->holding<<"  ";
    if (i%5==0){
      cout<<"\n\n";
    }
  }
  cout<<"\n"<<endl;

}
void break1(){}
void display_manager::set_surrounding() {
  for (int i=1;i<=25;i++) { // for each pair in the boxes
       switch ( boxes[i]->type ) {
         // check each type and then add the surrounding boxes
         // surrounding means when it expands where will the atoms go

                  case type::TOPLC: // this has only two
                          boxes[i]->surrounding.insert( boxes[i+1]);
                          boxes[i]->surrounding.insert(boxes[i+5]);

                   break;

                   case type::TOPRC:
                           boxes[i]->surrounding.insert( boxes[i-1]);
                           boxes[i]->surrounding.insert(boxes[i+5]);
                    break;

                 case type::TOP: //has three surrounding
                           boxes[i]->surrounding.insert( boxes[i-1]);
                           boxes[i]->surrounding.insert(boxes[i+1]);
                           boxes[i]->surrounding.insert(boxes[i+5]);
                   break;

                   case type::LEFT:
                             boxes[i]->surrounding.insert( boxes[i-5]);
                             boxes[i]->surrounding.insert(boxes[i+5]);
                             boxes[i]->surrounding.insert(boxes[i+1]);
                     break;

                   case type::RIGHT:
                               boxes[i]->surrounding.insert( boxes[i-1]);
                               boxes[i]->surrounding.insert(boxes[i+5]);
                               boxes[i]->surrounding.insert(boxes[i-5]);
                   break;

                   case type::BOTTOM:
                               boxes[i]->surrounding.insert( boxes[i-1]);
                               boxes[i]->surrounding.insert(boxes[i+1]);
                               boxes[i]->surrounding.insert(boxes[i-5]);
                    break;

                    case type::BOTTOMLC:
                                boxes[i]->surrounding.insert(boxes[i+1]);
                                boxes[i]->surrounding.insert(boxes[i-5]);
                     break;

                     case type::BOTTOMRC:
                                 boxes[i]->surrounding.insert(boxes[i-1]);
                                 boxes[i]->surrounding.insert(boxes[i-5]);
                      break;

                      case type::MIDDLE: // has four surrounding
                      boxes[i]->surrounding.insert(boxes[i-1]);
                      boxes[i]->surrounding.insert(boxes[i-5]);
                      boxes[i]->surrounding.insert(boxes[i+5]);
                      boxes[i]->surrounding.insert(boxes[i+1]);
                      break;


           }


  }
  break1();

}

void display_manager::set_type() {

  for(int i=1;i<=5;i++) { // for the first row

         if(i%5==1){  // if i is one it could be hardcoded anyway
           boxes[i]->type = type::TOPLC;
           boxes[i]->max =1; //sets maximum
         }
         else if(i%5==0) { // if it is the end of top row
           boxes[i]->type = type::TOPRC;
           boxes[i]->max =1; //sets maximum

         }
         else {
           boxes[i]->type = type::TOP; // otherwise it is a normal top
           boxes[i]->max =2; //sets maximum

         }
  }
  for(int i=6;i<=20;i++) {

         if(i%5==1){
           boxes[i]->type = type::LEFT; // if it is on the left
           boxes[i]->max =2; //sets maximum
         }
         else if(i%5==0) {
           boxes[i]->type = type::RIGHT; // if it is on the right
           boxes[i]->max =2; //sets maximum
         }
         else {
           boxes[i]->type = type::MIDDLE; // if it is a middle element
           boxes[i]->max =3; //sets maximum
         }
  }
  for(int i=21;i<=25;i++) { // bottom row

         if(i%5==1){
           boxes[i]->type = type::BOTTOMLC; // bottom row left
           boxes[i]->max =1; //sets maximum
         }
         else if(i%5==0) {
           boxes[i]->type = type::BOTTOMRC; // bottom row right
           boxes[i]->max =1; //sets maximum
         }
         else {
           boxes[i]->type = type::BOTTOM; // if it is a  normal bottom row element
           boxes[i]->max =2; //sets maximum
         }
  }
}

bool box::update() {
  if (rotation >= 360) {
    rotation = 2;
  }
  else {
    rotation+=2;
  }
return process_events();
}
bool box::process_events() {
  bool processed = true; //variable to check if no events are left
  for ( receive_results*  rr: event_queue ) { // its like  for i in list
    processed =false;                                  //in python
    received(rr); // send the pointer to the received event
    /* when something has come in then call receive which for now
     only adds the value of no of atoms in the box and checks it it max
     and if overflow then call explode
    */
  }
  event_queue = {}; // done with process_events so clear the queue
  return processed;
}

void box::received(receive_results* rr) { // the received function
  if (rr) {
     if (owner!=rr->owner) {
       if(owner)
        owner->holding--;
    owner = rr->owner;
    color = owner->color;
    owner->holding++;
    displayer->check =true;
  }

    delete rr;
  }
  if (holding == max) {
    holding =0;
    owner->holding--;
    explode(rr);  // check if the box already has the maximum number of atoms
  }
  else {
    holding+=1; // otherwise just add 1 to holding value
  }
  //displayer->printall();

}

void box::explode(receive_results *rr) {
   for( box* b : surrounding) {
     animation *a1  = new animation(b,this,displayer,owner);
     //make a new animation from this box to that surrounding box1

     displayer->current.insert(a1);
   }
   color.r=color.g=color.b=0;
   owner = nullptr;
}


//-----------------------------------------------------------------------------

int main() {
  display_manager d1;
  //receive_results r1(nullptr,nullptr);
  /*d1.user_event(1);
  d1.user_event(1);
  d1.user_event(1);
  d1.user_event(1);
  d1.user_event(1);
  d1.user_event(1);
 // calls 1 24 times
  d1.user_event(1);
  d1.user_event(1);
  d1.user_event(1);
  d1.user_event(1);
  d1.user_event(1);
  d1.user_event(1);

  d1.user_event(1);
  d1.user_event(1);
  d1.user_event(1);
  d1.user_event(1);
  d1.user_event(1);
  d1.user_event(1);

  d1.user_event(1);
  d1.user_event(1);
  d1.user_event(1);
  d1.user_event(1);
  d1.user_event(1);
  d1.user_event(1);

  d1.process_pending();
*/
d1.run();
  //SDL_Quit();
}
