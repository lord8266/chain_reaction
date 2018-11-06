#include <iostream>
using namespace std;


player::player(const int& i):holding(i) {

}

bool cycle(player** p) {
  *p = (*p)->next;
  cout<<(*p)->holding<<endl;
  return true;
}


int main() {
  player *first = new player(1);
  player *second = new player(2);
  player *third = new player(3);

  first->previous = third;
  first->next = second;

  second->next = third;
  second->previous=first;

  third->next = first;
  third->previous=second;

cycle(&first);
cycle(&first);
cycle(&first);
cycle(&first);
cycle(&first);

}
