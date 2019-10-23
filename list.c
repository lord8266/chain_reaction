#include "main.h"

list* alloc_list() {
    list *s = malloc(sizeof(list));
    s->len = 0;
    s->head = NULL;
    return s;
}

void dealloc_node(node *n,void(*dealloc)(void* )) {
    dealloc(n->data);
    free(n);
}
void dealloc_list(list *l) {
    node *n = l->head;
    for (int i=0;i<l->len;i++) {
        node *t = n->next;
        dealloc_node(n,free);
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

node *delete(list *l,node* n,void *data,int *size,void(*dealloc)(void*)) {

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
            }
            if (size) {
                *size = curr->size;
            }
            dealloc_node(curr,dealloc);
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
            }
            if (size)
                 *size = curr->size;
            dealloc_node(curr,free);
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

queue *alloc_queue(int max) {
    queue *q = malloc(sizeof(queue));
    q->l = alloc_list();
    q->max = max;
    return q;
}
void d(void* v) {
    dealloc_save(v);
}
void dealloc_queue(queue *q) {
    node *curr = q->l->head;
    while(curr) {
        curr = delete(q->l,curr,NULL,NULL,d);
    }
    dealloc_list(q->l);
    free(q);
}
void push_queue(queue *q,save *data) {
    
    if (q->max==q->l->len) {
        save *s= malloc(sizeof(save));
        delete_pos(q->l,0,s,NULL);
        dealloc_save(s);
    }
    push(q->l,data,sizeof(save));
}

int pop_queue(queue *q,save *s) {
    if (q->l->len) {
        delete_pos(q->l,q->l->len-1,s,NULL);
        return 1;
    }
    else {
        return 0;
    }
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