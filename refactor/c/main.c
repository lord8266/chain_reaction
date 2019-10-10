#include "main.h"

// int main() {
    // state *s = alloc_state(10,10,update);
    // print_layout(s->board);
    // add(s,0,0,1,0);
    // complete(s);
    // add(s,0,1,2,0);
    // complete(s);
    // add(s,0,1,2,0);
    // complete(s);
    // print_atoms(s->board);
    // add(s,0,0,1,0);
    // complete(s);
    // print_atoms(s->board);
    // dealloc_state(s);
// }

int main() {
    player p[3];
    write_player(&p[0],1);
    write_player(&p[1],1);
    write_player(&p[2],1);

    state *s = alloc_state(10,10,p,3);
    print_layout(s->board);
    print_atoms(s->board);
    while (!s->completed) {
        continue_game(s);
    }

}