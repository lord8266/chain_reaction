//-------------------- display_manager --------------------


#include "display_manager.h"

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
  w1 = SDL_CreateWindow("test",640,480,500,500,SDL_WINDOW_SHOWN);
  w_ren = SDL_CreateRenderer(w1,-1,SDL_RENDERER_ACCELERATED| SDL_RENDERER_PRESENTVSYNC);
  //make_textures(); // make all textures need to display on
  make_atoms();
  r_text.w=50;
  r_text.h = 50;
}

//----------------------------------------------------------------------

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

//----------------------------------------------------------------------

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

//----------------------------------------------------------------------

void display_manager::print_location() {
  for (int i=1;i<=5;i++ ) {
    for(int j=1 ;j<=5;j++) {


    coordinates *temp = boxes[i+5*(j-1)]->location;
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
     run_check();
   }
   running = current.size()==0 && temp_running;
}

}

//----------------------------------------------------------------------

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

//----------------------------------------------------------------------

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

//----------------------------------------------------------------------

void display_manager::printall() { //printing function
  for (int i=1;i<=25;i++) {

    cout<<boxes[i]->holding<<"  ";
    if (i%5==0){
      cout<<"\n\n";
    }
  }
  cout<<"\n"<<endl;

}

//----------------------------------------------------------------------

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

}

//----------------------------------------------------------------------

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

//----------------------------------------------------------------------

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

//------------------------------------------------------------------------------

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

//----------------------------------------------------------------------
