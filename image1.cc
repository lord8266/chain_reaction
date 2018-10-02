#include "header.h"
#include <SDL.h>
#include <SDL_image.h>

int main() {
  SDL_Init(SDL_INIT_VIDEO);
  IMG_Init(IMG_INIT_PNG);
  SDL_Window *w1 = SDL_CreateWindow("test1",640,480,640,480,SDL_WINDOW_SHOWN);
  SDL_Renderer *w_ren = SDL_CreateRenderer(w1,-1,SDL_RENDERER_ACCELERATED|SDL_RENDERER_PRESENTVSYNC);
  int x,y;
  SDL_Surface *s1 = IMG_Load("img/a2.png");
  SDL_Texture * t1 = SDL_CreateTextureFromSurface(w_ren,s1);
  SDL_FreeSurface(s1);
  SDL_Event e;
  bool running = true;
SDL_Rect r1;
/*SDL_Rect triple;
SDL_Point p1{.x =52,.y=51};
triple.x = 165;
triple.y = 28;
triple.w = 107;
triple.h = 136;*/

r1.x =r1.y=0;
r1.w =50;
r1.h = 50;
double angle = 0.0;
  while(running) {
    while(SDL_PollEvent(&e)) {
      switch(e.type) {
        case SDL_QUIT:
         running = false;
        break;
    }
  }
    SDL_GetMouseState(&x,&y);
    SDL_RenderClear(w_ren);
    if (angle>=360)
      angle = 0;
    angle+=5;
    SDL_RenderCopyEx(w_ren,t1,nullptr,&r1,angle,nullptr,SDL_FLIP_NONE);
    SDL_RenderPresent(w_ren);

    cout<<x<< " "<<y<<endl;
  }
SDL_Quit();
}
