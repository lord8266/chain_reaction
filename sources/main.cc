#include "main.h"

//int animation::speed = 4;
int main() {
  int a1=8;
  cout<<a1<<endl;
  SDL_Rect r1;
  r1.x = 6;
  r1.y=6;
  r1.w=50;
  r1.h=50;

  ifstream file_in("players.txt");
  string temp="";
  vector<player*> data;
  while (getline(file_in,temp)) {
    int r,g,b;
    istringstream str1(temp);
    str1>>temp;
    str1>>r>>g>>b;
    //cout<<r<<" "<<(int)g<<" "<<(int)b<<endl;
    data.push_back(new player(temp,{r,g,b}));

  }
  display_manager d1(data,r1);
  d1.run();
}
