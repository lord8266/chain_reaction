#include "main.h"

list* alloc_list() {
    list *s = malloc(sizeof(list));
    s->len = 0;
    s->head = NULL;
    return s;
}

void dealloc_node(node *n) {
    free(n->data);
    free(n);
}
void dealloc_list(list *l) {
    node *n = l->head;
    for (int i=0;i<l->len;i++) {
        node *t = n->next;
        dealloc_node(n);
        n = t;
    }
    free(l);
}


node *alloc_node(void *data,int size) {
    void *d = malloc(size);
    memcpy(d,data,size);
    node *n = malloc(sizeof(node));
    n->next = NULL;
    n->data = d;
    n->size = size;
    return n;
}

node * push(list *l,void *data,int size) {
    node *in = alloc_node(data,size);
    if (l->len==0) {
        l->head = in;   
    }
    else {
        node *curr = l->head;
        while (curr->next && (curr=curr->next));
        curr->next = in;
    }
    l->len+=1;
    return in;
}

node *delete(list *l,node* n,void *data,int *size) {

    if(l->len>=1) {
        node *curr = l->head;
        node *prev = NULL;
        while (curr!=n ) {
            prev =curr;
            curr =curr->next;
        }

        if (curr==n) {
            node *ret =NULL;
            node *n =curr->next;
            ret = n;
            if (data) {
                memcpy(data,curr->data,curr->size);
                *size = curr->size;
            }
            dealloc_node(curr);
            if (prev==NULL) {
                l->head = n;
            }
            else {
                prev->next = n;
            }

            l->len-=1;
            return ret;
        }  
    }
    
    return NULL;
    
}

node *delete_pos(list *l,int pos,void *data,int *size) {

    if(l->len>=1) {
        int i =0;
        node *curr = l->head;
        node *prev = NULL;
        while (curr &&  i!=pos) {
            prev =curr;
            curr =curr->next;
            i+=1;
        }

        if (i==pos) {
            node *ret =NULL;
            node *n =curr->next;
            ret = n;
            if (data) {
                memcpy(data,curr->data,curr->size);
                *size = curr->size;
            }
            dealloc_node(curr);
            if (prev==NULL) {
                l->head = n;
            }
            else {
                prev->next = n;
            }

            l->len-=1;
            return ret;
        }  
    }
    
    return NULL;
    
}

void print(list *l) {
    node *curr = l->head;
    for (int i=0;i<l->len;i++) {
        printf("%d\n",*(int*)curr->data);
        curr =curr->next;
    }
}
// int main() {
//     int i[10] ={1,2,3,4,5,6,7,8,9,10};
//     list *l = alloc_list();
//     push(l,(void*)&i[0],4);
//     push(l,(void*)&i[1],4);
//     node *t = delete_pos(l,0,NULL,NULL);
//     printf("%d\n",*(int*)t->data);
//     // node *tdelete(l,l->head,NULL,NULL);
//     print(l);
//     dealloc_list(l);
// }