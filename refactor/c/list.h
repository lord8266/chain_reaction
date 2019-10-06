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
void push(list*,void*,int);
node *delete(list*,int pos,void *,int *);


#endif