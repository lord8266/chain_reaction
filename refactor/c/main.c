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
    color c ={0,0,0,255};
    write_player(&p[0],c);
    write_player(&p[1],c);
    write_player(&p[2],c);
    base *b = alloc_base(640,640,6,6,p,3);
    print_layout(b->s->board);
    print_atoms(b->s->board);
    // while (!b->s->completed) {
    //     continue_game(b->s);
    // }
    while(b->running) {
        run(b);
    }
    dealloc_base(b);
}