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

typedef struct queue {
    list *l;
    int max;
}queue;

list* alloc_list();
void dealloc_list(list *);

node *alloc_node(void *data,int size);
node* push(list*,void*,int);
node *delete(list* l,node* n,void *data,int *size,void(*)(void*));
node *delete_pos(list *l,int pos,void *data,int *size);

queue* alloc_queue(int max);
void dealloc_queue(queue *q);
void push_queue(queue *q,save *);
int pop_queue(queue *q,save *);
#endif