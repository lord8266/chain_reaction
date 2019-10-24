#ifndef list_
#define list_
#include "main.h"
struct node {
    int size;
    void *data;
    node *next;
};

struct list {
    node *head;
    node *end;
    int len;
};

typedef struct stack {
    list *l;
    int max;
}stack;

list* alloc_list();
void dealloc_list(list *);

node *alloc_node(void *data,int size);
node* push(list*,void*,int);
node *delete(list* l,node* n,void *data,int *size);
node *delete_pos(list *l,int pos,void *data,int *size);

stack* alloc_stack(int max);
void dealloc_stack(stack *q);
void push_stack(stack *q,void *,int );
int pop_stack(stack *q,void *,int *);
node* peek_stack(stack*);
void remove_all(list *l);
#endif