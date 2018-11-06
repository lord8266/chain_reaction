//-------------------- display_manager --------------------


#include "display_manager.h"

display_manager::display_manager(const vector<player*> &data,const SDL_Rect& r):
boxes(nullptr),
e1(new event_manager(this)),
game_details(new SDL_Rect(r)),
game_control(new game_base(data,this)) { //initalize both sets to nothing
                                                    //set is the same as in python
                                                    // make a event handler to handle events
SDL_Rect temp;
int rows =game_details->y;
int cols =game_details->x;


temp.w = game_details->w;
temp.h = game_details->h;

boxes = alloc.allocate(rows*cols);

  for (int i=0;i<rows;i++) { // for each row

    for (int j=0;j<cols;j++) { // for each column

      int id = j + i*cols;
      temp.x = j*temp.w;
      temp.y = i*temp.h;
      alloc.construct(boxes+id,id, temp , this);


      //      id    , x coordinate ,y cooridinate , pointer to displayer
// the +25 is for shift of coordinates just try it out yourself how you would do it
      //  apparently gaming engines use the fourth quadrant
      //  hence the negative sign on j

  }
}

  set_type(); // sets the type and maximum of each box
  set_surrounding(); // sets the surrounding &boxes of each box
  setup(); // setup the SDL side
  color_change(0);
  main_running =true;
}


//----------------------------------------------------------------------

void display_manager::run_check() {

    check = false;
game_control->update();

}

//----------------------------------------------------------------------

void display_manager::remove_animation(animation* a_d) {
  current.erase(a_d);
  delete a_d;
}

//----------------------------------------------------------------------

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

void display_manager::end_texture_create() {
  TTF_Init(); // initialize ttf
  TTF_Font *temp_font = TTF_OpenFont("textures/arial.ttf",25); // take font from arial
  player *winner = *(game_control->current); // make a color variable
  string msg = winner->name + " wins  " ;
  string msg2 = "while owning "+ std::to_string(winner->holding) + " boxes";
  SDL_Surface *temp = TTF_RenderText_Solid(temp_font,msg.c_str(),*winner->color); // render text
  ending = SDL_CreateTextureFromSurface(w_ren,temp);
  int width = game_details->w*game_details->x;
  int height =game_details->h*game_details->y;
  endpos.x = width/3;
  endpos.y = height/2;
  endpos.w = temp->w;
  endpos.h = temp->h;
  SDL_FreeSurface(temp);
  temp = TTF_RenderText_Solid(temp_font,msg2.c_str(),*winner->color); // render text
  ending2 = SDL_CreateTextureFromSurface(w_ren,temp);

  endpos2.x = width/3-45;
  endpos2.y = height/2+ endpos.h;
  endpos2.w = temp->w;
  endpos2.h = temp->h;
  SDL_FreeSurface(temp);
}
//----------------------------------------------------------------------

void display_manager::quit(){
  //SDL_Quit();
  //cout<<"here"<<endl;
  main_running = false;

}

//----------------------------------------------------------------------

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

//----------------------------------------------------------------------

void display_manager::texture_mod(const int& tex_index,const int& i) {
  static Uint8 r,g,b; // static values cause need to store them
  if(i) { // if i need to revert back to the previous color being used
      SDL_SetTextureColorMod(value_maps[tex_index],r,g,b); // set the colors
  }
  else {
    SDL_GetTextureColorMod(value_maps[tex_index],&r,&g,&b); //get the colors to rgba
  }
}

//----------------------------------------------------------------------

void display_manager::draw_grid() {
  color_change(0);
  int width = game_details->x*game_details->w;
  int height = game_details->y*game_details->h;

  if(!running) { // running is false when animation is going on
   SDL_SetRenderDrawColor(w_ren,255,255,255,255);
  }
  else {

  SDL_SetRenderDrawColor(w_ren,grid_color->r,grid_color->g,grid_color->b,255);
}
  for (int i=0;i<height;i+=game_details->h) {
    SDL_RenderDrawLine(w_ren,0,i,width,i);
  }
  SDL_RenderDrawLine(w_ren,0,height-1,width,height-1);
  for (int i=0;i<width;i+=game_details->w) {
    SDL_RenderDrawLine(w_ren,i,0,i,height);
  }
  SDL_RenderDrawLine(w_ren,width-1,0,width-1,height);
  color_change(1);
}

//----------------------------------------------------------------------

void display_manager::user_event(const int& i) { // user event
  //process_pending();
  // go through all animations before doing anything
  game_control->user_event(i);
  /* if user clicks on a box then send an event to the corresponding box
     since im now sending a nullptr the box would identify that it is a user event
     and im using the same flow as before
     */

}

//----------------------------------------------------------------------

void display_manager::setup() {
  SDL_Init(SDL_INIT_VIDEO);
  int width = game_details->x*game_details->w;
  int height = game_details->y*game_details->h;
  int num = SDL_GetNumVideoDrivers();
  for (int i=0;i!=num;i++) {
    cout<<"driver : "<<SDL_GetVideoDriver(i)<<endl;
  }
  w1 = SDL_CreateWindow("chainreaction2d",640,480,width,height,SDL_WINDOW_SHOWN);
  w_ren = SDL_CreateRenderer(w1,-1,SDL_RENDERER_ACCELERATED| SDL_RENDERER_PRESENTVSYNC);
  //make_textures(); // make all textures need to display on
  make_atoms();
}

//----------------------------------------------------------------------

void display_manager::make_atoms() {
  IMG_Init(IMG_INIT_PNG);
  SDL_Surface *s_temp = IMG_Load("new_img/a11.png");
  SDL_Texture *t1  = SDL_CreateTextureFromSurface(w_ren,s_temp);
  value_maps.insert({1,t1});
  SDL_FreeSurface(s_temp);

  s_temp = IMG_Load("new_img/a22.png");
  t1  = SDL_CreateTextureFromSurface(w_ren,s_temp);
  value_maps.insert({2,t1});
  SDL_FreeSurface(s_temp);

  s_temp = IMG_Load("new_img/a33.png");
  t1  = SDL_CreateTextureFromSurface(w_ren,s_temp);
  value_maps.insert({3,t1});
  SDL_FreeSurface(s_temp);
 IMG_Quit();

}

//----------------------------------------------------------------------

void display_manager::print_location() {
  for (int i=1;i<=5;i++ ) {
    for(int j=1 ;j<=5;j++) {


    SDL_Rect *temp = boxes[i+5*(j-1)].location;
  //  cout<<"( "<<temp->x<< " , "<<temp->y<<" )  ";
  }
  cout<<endl;
  }
}

//----------------------------------------------------------------------

void display_manager::process_pending() {
      // till animations isnt zero go on running
     // call run

    while ((!update())||(current.size()!=0)){ // magically does the job of
                                              // processing all events and animations
      run();  // call run
    }
}

//----------------------------------------------------------------------

void display_manager::run() {
  bool temp_running = false;
  while (main_running) {
    process_events(); // process all events;
    temp_running = update(); //call update
   render(); //call render
   if (check) {
     update();
     run_check();
   }
   running = current.size()==0 && temp_running;
}

}

//----------------------------------------------------------------------

bool display_manager::update() {
  bool updated = true;
  for (int i=0;i<game_details->x*game_details->y;i++) {
    if(!boxes[i].update())
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

//----------------------------------------------------------------------

void display_manager::render() {
  SDL_RenderClear(w_ren);
  draw_grid();
  render_atom_count();
  if(end_displaying) {
    SDL_Rect r_temp;
    r_temp.x = endpos.x-endpos.w/2-55;
    r_temp.y =endpos.y-5;
    r_temp.w = endpos.w+endpos2.w+10;
    r_temp.h = endpos.h+endpos2.h+10;
    color_change(0);
    SDL_SetRenderDrawColor(w_ren,255,255,255,255);
    SDL_RenderFillRect(w_ren,&r_temp);
    color_change(1);
    SDL_RenderCopy(w_ren,ending,nullptr,&endpos);
    SDL_RenderCopy(w_ren,ending2,nullptr,&endpos2);

  }
  color_change(0);
  SDL_SetRenderDrawColor(w_ren,30,40,50,60);
  for( animation* a_anim: current) {
    a_anim->run();
  }
  color_change(1);
  SDL_RenderPresent(w_ren);
  //cout<<running<<endl;
}

//----------------------------------------------------------------------

void display_manager::printall() { //printing function
  for (int i=1;i<=25;i++) {

    cout<<boxes[i].holding<<"  ";
    if (i%5==0){
      cout<<"\n\n";
    }
  }
  cout<<"\n"<<endl;

}

//----------------------------------------------------------------------

void display_manager::set_surrounding() {
  int cols=game_details->x;
  int rows =game_details->y;
  for (int i=0;i<rows*cols;i++) { // for each pair in the &boxes
       switch ( boxes[i].type ) {

         // check each type and then add the surrounding &boxes
         // surrounding means when it expands where will the atoms go

                  case type::TOPLC: // this has only two
                          boxes[i].surrounding.insert( &boxes[i+1]);
                          boxes[i].surrounding.insert(&boxes[i+cols]);

                   break;

                   case type::TOPRC:
                           boxes[i].surrounding.insert( &boxes[i-1]);
                           boxes[i].surrounding.insert(&boxes[i+cols]);
                    break;

                 case type::TOP: //has three surrounding
                           boxes[i].surrounding.insert( &boxes[i-1]);
                           boxes[i].surrounding.insert(&boxes[i+1]);
                           boxes[i].surrounding.insert(&boxes[i+cols]);
                   break;

                   case type::LEFT:
                             boxes[i].surrounding.insert( &boxes[i-cols]);
                             boxes[i].surrounding.insert(&boxes[i+cols]);
                             boxes[i].surrounding.insert(&boxes[i+1]);
                     break;

                   case type::RIGHT:
                               boxes[i].surrounding.insert( &boxes[i-1]);
                               boxes[i].surrounding.insert(&boxes[i+cols]);
                               boxes[i].surrounding.insert(&boxes[i-cols]);
                   break;

                   case type::BOTTOM:
                               boxes[i].surrounding.insert( &boxes[i-1]);
                               boxes[i].surrounding.insert(&boxes[i+1]);
                               boxes[i].surrounding.insert(&boxes[i-cols]);
                    break;

                    case type::BOTTOMLC:
                                boxes[i].surrounding.insert(&boxes[i+1]);
                                boxes[i].surrounding.insert(&boxes[i-cols]);
                     break;

                     case type::BOTTOMRC:
                                 boxes[i].surrounding.insert(&boxes[i-1]);
                                 boxes[i].surrounding.insert(&boxes[i-cols]);
                      break;

                      case type::MIDDLE: // has four surrounding
                      boxes[i].surrounding.insert(&boxes[i-1]);
                      boxes[i].surrounding.insert(&boxes[i-cols]);
                      boxes[i].surrounding.insert(&boxes[i+cols]);
                      boxes[i].surrounding.insert(&boxes[i+1]);
                      break;


           }


  }

}

//----------------------------------------------------------------------

void display_manager::set_type() {

  int cols = game_details->x;
  int rows = game_details->y;
  int i=0;
  boxes[i].type=type::TOPLC;
  boxes[i].max = 1;
  for(i=1;i<cols-1;i++) { // for the first row

           boxes[i].type = type::TOP; // otherwise it is a normal top
           boxes[i].max =2; //sets maximum

    }

  boxes[i].type = type::TOPRC;
  boxes[i].max =1; //sets maximum
  i++;
  for(;i<(rows-1)*cols;i++) {

         if(i%cols==0){
           boxes[i].type = type::LEFT; // if it is on the left
           boxes[i].max =2; //sets maximum
         }
         else if( (i+1)%cols==0) {
           boxes[i].type = type::RIGHT; // if it is on the right
           boxes[i].max =2; //sets maximum
         }
         else {
           boxes[i].type = type::MIDDLE; // if it is a middle element
           boxes[i].max =3; //sets maximum
         }
  }
  boxes[i].type=type::BOTTOMLC;
  boxes[i].max = 1;
  i++;

  for(;i<rows*cols-1;i++) { // bottom row

          boxes[i].type = type::BOTTOM;
           boxes[i].max =2;

  }
  boxes[i].type = type::BOTTOMRC; // bottom row right
  boxes[i].max =1; //sets maximum
}

//----------------------------------------------------------------------

void display_manager::render_atom_count() {
  box *temp = nullptr; // set the bopx operating on
  int holding =0;
  SDL_Rect r_text ;
  r_text.w = game_details->w;
  r_text.h =game_details->h;
  for (int i=0;i<game_details->x*game_details->y;i++) { // go in range of &boxes
    temp = &boxes[i];
    holding = temp->holding;

    if (temp->color) {
      texture_mod(holding,0);
      SDL_SetTextureColorMod(value_maps[holding],temp->color->r,temp->color->g,temp->color->b);
        r_text.x = temp->location->x;
        r_text.y = temp->location->y;
}

SDL_RenderCopyEx(w_ren,value_maps[holding],nullptr,&r_text,temp->rotation,nullptr,SDL_FLIP_NONE);
texture_mod(holding,1);
}
  }


//------------------------------------------------------------------------------

display_manager::~display_manager() {
  for (int i=0;i<game_details->x*game_details->y;i++) {
    alloc.destroy(boxes+i);
  }
  alloc.deallocate(boxes,game_details->x*game_details->y);

  for (auto a: value_maps) {
    SDL_DestroyTexture(a.second);
  }
  SDL_DestroyRenderer(w_ren);
  SDL_DestroyWindow(w1);
  SDL_Quit();
}

//----------------------------------------------------------------------
