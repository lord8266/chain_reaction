#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct node {
    void *data;
    struct node *next;
}node;

typedef struct list {
    node *start;
    int len;
}list;

list* alloc_list() {
    list *s = malloc(sizeof(list));
    s->len = 0;
    s->start = 0;
    s->start = NULL;
    return s;
}

node *alloc_node(void *data,int size) {
    void *d = malloc(size);
    memcpy(d,data,size);
    node *n = malloc(sizeof(node));
    n->next = NULL;
    n->data = d;
    return n;
}