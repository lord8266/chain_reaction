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
    int len;
};

list* alloc_list();
void dealloc_list(list *);

node *alloc_node(void *data,int size);
node* push(list*,void*,int);
node *delete(list* l,node* n,void *data,int *size);
node *delete_pos(list *l,int pos,void *data,int *size);

#endif