#include "main.h"

int main() {
    player p[3];
    color c[3] ={   {255,0,0,255},
                    {0,255,0,255},
                    {0,0,255,255}
                };
    write_player(&p[0],c[0]);
    write_player(&p[1],c[1]);
    write_player(&p[2],c[2]);
    base *b = alloc_base(100,5,5,p,3);
    print_layout(b->s->board);
    while(b->running) {
        run(b);
    }

    dealloc_base(b);
}