#include "main.h"

void write_player(player *p) {
    scanf("%hhd %hhd %hhd %hhd %s",&p->c.r,&p->c.g,&p->c.b,&p->c.a,p->name);
    p->start = p->n = 0;
}
void print_checkpoint_size(state *s) {
    printf("Checkpoint Size\n");
    printf("%-10s: %d bytes\n","Box",s->save_box_size);
    printf("%-10s: %d bytes\n","Player",s->save_player_size);
    printf("%-10s: %d bytes\n","ALive",s->save_alive_size);
    printf("%-10s: %ld bytes\n","CurrPlayer",sizeof(int));
    printf("%-10s: %ld bytes\n","Total",s->save_box_size+s->save_player_size+ s->save_alive_size + sizeof(int) );
}

int main() {
    int rows,cols,box_size,n_players;
    scanf("%d %d %d %d",&rows,&cols,&box_size,&n_players);
    player *p = malloc(sizeof(player)*n_players);
    for (int i=0;i<n_players;i++) 
        write_player(p+i);
    base *b = alloc_base(box_size,rows,cols,p,n_players);

    print_layout(b->s->board);
    putchar('\n');
    print_checkpoint_size(b->s);
    putchar('\n');

    while(b->running) {
        run(b);
    }

    dealloc_base(b);
    free(p);
}