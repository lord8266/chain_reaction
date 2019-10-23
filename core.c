#include "main.h"

void write_box(box *b,int row,int col,int max,pos *p,int *index) {
    b->position.row= row;
    b->position.col =col; 
    b->atoms = 0;
    b->max =max;
    memcpy(b->surrounding,p,sizeof(pos)*4);
    b->player =-1;
    memcpy(b->index,index,sizeof(int)*4);
}

pos *neighbours(int i,int j,int rows,int cols,int *index,int *size) {
    int n=0;
    pos *p = malloc(sizeof(pos) * 4);
    memset(index,0,16);
    if (i > 0)
    {
        p[0].row = i - 1;
        p[0].col = j;
        n += 1;
        index[0] =1;
    }
    if (i < (rows - 1))
    {
        p[1].row = i + 1;
        p[1].col = j;
        n += 1;
        index[1] =1;
    }
    if (j < (cols - 1))
    {
        p[2].row = i;
        p[2].col = j + 1;
        n += 1;
        index[2] =1;;
    }
    if (j > 0)
    {
        p[3].row = i;
        p[3].col = j - 1;
        n += 1;
        index[3] =1;
    }
   
    *size =n;

    return p;
}

layout *alloc_layout(int rows,int cols) {
    layout *l = malloc(sizeof(layout));
    l->rows = rows;
    l->cols =cols;
    box *b = malloc(sizeof(box)*rows*cols);
    int index[4];
    for (int i=0;i<rows;i++) {
        for (int j=0;j<cols;j++) {
            int size;
            pos *p =neighbours(i,j,rows,cols,index,&size);
            write_box(&b[i*cols+j],i,j,size-1,p,index);
            free(p);
        }
    }
    l->boxes =b;
    return l;
}

void print_layout(layout *l) {
    for (int i=0;i<l->rows;i++) {
        for (int j=0;j<l->cols;j++) {
            printf("(%d, %d) -> ",i,j);
            box *b = &l->boxes[i*l->cols+j];
            for (int k=0;k<=3;k++) {
                if (b->index[k])
                    printf("(%d, %d) ",b->surrounding[k].row,b->surrounding[k].col);
            }
            printf(" %d\n",b->max);
        }
    }
}

void dealloc_layout(layout *l) {
    free(l->boxes);
    free(l);
}

void checkpoint(base *b) {

    push_queue(b->s->checkpoints,b->s->prev);
    printf("SIze: %d\n",b->s->checkpoints->l->len);
    save *p = b->s->prev;
    b->s->prev = alloc_save(b);
    free(p);
}

int rollback(base *b) {
    
    if (b->s->checkpoints->l->len) {
        save *prev = malloc(sizeof(save));
        pop_queue(b->s->checkpoints,prev);
        list *ongoing_state = b->s->ongoing;
        node *curr  = ongoing_state->head;
        while(curr) {
            curr = delete(ongoing_state,curr,NULL,NULL,free);
        }
        ongoing_state->len = 0;
        list *ongoing_animations = b->r->ongoing;
        curr  = ongoing_animations->head;
        while(curr) {
            curr = delete(ongoing_animations,curr,NULL,NULL,free);
        }
        int rows = b->s->board->rows;
        int cols = b->s->board->cols;

        memcpy(b->s->board->boxes,prev->boxes,sizeof(box)*rows*cols);
        memcpy(b->s->players,prev->players,sizeof(player)*b->s->n_players);
        memcpy(b->s->alive,prev->alive,sizeof(int)*b->s->n_players);
        b->s->curr = prev->curr;
        dealloc_save(b->s->prev);
        b->s->prev = prev;
        return 1;
    }
    else {
        return 0;
    }

}
state* alloc_state(int rows,int cols,player *players,int size,base *b) {
    state *s = malloc(sizeof(state));
    s->board = alloc_layout(rows,cols);
    s->ongoing = alloc_list();
    // s->update =u;
    s->players = malloc(sizeof(player)*size);
    memcpy(s->players,players,sizeof(player)*size);
    s->alive = malloc(4*size);
    for (int i=0;i<size;i++) {
        s->alive[i] =1;
    }
    s->curr = 0;
    s->completed = 0;
    s->n_players = size;
    s->b = b;
    s->checkpoints = alloc_queue(30);

    return s; 
}

player *alloc_player(color c) {
    player *p = malloc(sizeof(player));
    p->start =0;
    p->c = c;
    p->n = 0;
    return p;
}

void write_player(player *p,color c) {
    p->start =0;
    p->c = c;
    p->n = 0;
}

void cycle(state *s) {
    int i = s->curr;
    int curr = (i+1)%s->n_players;
    while (i!=curr && !s->alive[curr] ) {
        curr = (curr+1)%s->n_players;
    }
    
    s->curr = curr;
    
}
void write_explosion(explosion *e,pos from,pos to,int player) {
    e->from = from;
    e->to = to;
    e->player =player;
    e->completed =0;
}

void dealloc_state(state *s) {
    dealloc_layout(s->board);
    dealloc_list(s->ongoing);
    free(s->players);
    free(s->alive);
    dealloc_save(s->prev);
    dealloc_queue(s->checkpoints);
    free(s);
}

void dealloc_player(player *p) {
    // free(p);
}

int continue_game(state *s,int i,int j) {
    int p =s->curr;
    int ret = add(s,i,j,p,0);
    if (ret){
        if (ret==1)
            cycle(s);
        return 1;
    }
    else {
        return 0;
    }
    
}

int add(state *s,int i,int j,int player,int force) {
    box *b = &s->board->boxes[i*s->board->cols+j];
    int ret=1;
    if (!force && !(b->player==player || b->player==-1)) {
        return 0;
    }
    if (!force) {
        update(s,player,1);
    }
    else {
        if (b->player!=player) {
            update(s,player,b->atoms);
            if (b->player!=-1)
                update(s,b->player,-b->atoms);
        }
    }

    if (b->atoms==b->max) {
        b->atoms =0;
        explosion e;
        for (int i=0;i<4;i++) {
            if (b->index[i]==1) {
                write_explosion(&e,b->position,b->surrounding[i],player);
                node *n = push(s->ongoing,&e,sizeof(e));
                new_animation(s->b,(explosion*)n->data,5);
            }   
        }
        b->player =-1;
        ret =2;
    }
    else {
        b->player = player;
        b->atoms++;
    }
return ret;
}

int step(state *s) {
    if (s->completed || s->ongoing->len==0)
        return 0;
    
    node *curr = s->ongoing->head;
    list *l = alloc_list();
    explosion *e_copy = malloc(sizeof(explosion));
    int size;
    while(curr) {
        int explosion_completed = ((explosion*)curr->data)->completed;
        if (explosion_completed) { //improvise
            curr = delete(s->ongoing,curr,e_copy,&size,free);
            push(l,e_copy,sizeof(explosion));
        }
        else {
            curr = curr->next;
        }
    }

    curr = l->head;
    while(curr) {
        explosion *e  =curr->data;
        add(s,e->to.row,e->to.col,e->player,1);
        curr =curr->next;
    }
    dealloc_list(l);
    free(e_copy);
    return 1;

}

void complete(state *s) {
    while(step(s));
}

void print_atoms(layout *l) {
    for (int i=0;i<l->rows;i++) {
        for (int j=0;j<l->cols;j++) {
            box *b = &l->boxes[i*l->cols+j];
            printf("(%d, %d) ",b->atoms,b->player);
        }
        putchar('\n');
    }
}


save* alloc_save(base *b) {
    int rows =b->s->board->rows ,cols=b->s->board->cols;
    save *s = malloc(sizeof(save));
    s->alive =malloc(sizeof(int)*b->s->n_players);
    s->boxes = malloc(sizeof(box)*rows*cols);
    s->players = malloc(sizeof(player)*b->s->n_players);

    memcpy(s->boxes,b->s->board->boxes,sizeof(box)*rows*cols);
    memcpy(s->players,b->s->players,sizeof(player)*b->s->n_players);
    memcpy(s->alive,b->s->alive,sizeof(int)*b->s->n_players);
    s->curr = b->s->curr;
    return s;
}
void dealloc_save(save *s) {
    free(s->boxes);
    free(s->players);
    free(s->alive);
    free(s);
}
void update(state *s,int p1,int u1) {
    player *p = &s->players[p1];
    p->start =1;
    p->n+=u1;
    printf("update %d: %d\n",p1,u1);
    if (p->n==0) {
        s->alive[p1] = 0;
        printf("kill %d\n",p1);
    }
    int c = 0;
    for (int i=0;i<s->n_players;i++) {
        if (s->alive[i]) {
            c+=1; 
        }
    }
    s->completed = c==1;
}