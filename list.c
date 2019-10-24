#include "main.h"

list* alloc_list() {
    list *s = malloc(sizeof(list));
    s->len = 0;
    s->head = NULL;
    s->end = NULL;
    return s;
}

void dealloc_node(node *n) {
    free(n->data);
    free(n);
}

void remove_all(list *l) {
    node *n = l->head;
    for (int i=0;i<l->len;i++) {
        node *t = n->next;
        dealloc_node(n);
        n = t;
    }
    l->head = l->end = NULL;
    l->len = 0;
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
        l->end = in; 
    }
    else {
        node *curr = l->head;
        while (curr->next && (curr=curr->next));
        curr->next = in;
        l->end = in;
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
            }
            if (size) {
                *size = curr->size;
            }
            if (curr==l->end) {
                l->end = prev;
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
            }
            if (size)
                 *size = curr->size;

            if (curr==l->end) {
                l->end = prev;
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

stack *alloc_stack(int max) {
    stack *q = malloc(sizeof(stack));
    q->l = alloc_list();
    q->max = max;
    return q;
}

node *peek_stack(stack *q) {
    return q->l->end;
}

void dealloc_stack(stack *q) {
    node *curr = q->l->head;
    while(curr) {
        curr = delete(q->l,curr,NULL,NULL);
    }
    dealloc_list(q->l);
    free(q);
}
void push_stack(stack *q,void *data,int size) {
    
    if (q->max==q->l->len) {
        delete_pos(q->l,0,NULL,NULL);
    }

    push(q->l,data,size);
}

int pop_stack(stack *q,void *data,int *size) {
    if (q->l->len) {
        delete_pos(q->l,q->l->len-1,data,size);
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
//     // list *l = alloc_list();
//     // push(l,&i[0],sizeof(int));
//     // push(l,&i[1],sizeof(int));
//     // node *t = delete_pos(l,0,NULL,NULL);
//     // // node *tdelete(l,l->head,NULL,NULL);
//     // print(l);

//     // dealloc_list(l);

//     stack *q = alloc_stack(100);
//     push_stack(q,i+9,sizeof(int));
//     printf("%p %p\n",q->l->end,q->l->head);
//     node *n = peek_stack(q);
//     push_stack(q,i+3,sizeof(int));
    
//     printf("%d\n",*(int*)(n->data));
//     pop_stack(q,NULL,NULL);
//     n = peek_stack(q);
//     printf("%d\n",*(int*)(n->data));
    
//     pop_stack(q,NULL,NULL);
//     printf("%p\n",q->l->end);
    
// }