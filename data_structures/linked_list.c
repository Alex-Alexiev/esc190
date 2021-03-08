#include<stdlib.h>
#include<stdio.h>

#include "linked_list.h"

typedef struct ll_node {
    void *data; 
    struct ll_node *next; 
} ll_node; 

typedef struct ll_{
    ll_node *head;
} ll_;

typedef struct ll_iterator{
    ll_node *curr;
} ll_iterator;

ll_ *ll_create(){
    ll_ *new_ll = (ll_ *)malloc(sizeof(ll_));
    new_ll->head = NULL;
    return new_ll;
}

ll_node *ll_create_node(void *data){
    ll_node *new_node = (ll_node *)malloc(sizeof(ll_node));
    new_node->next = NULL;
    new_node->data = data;
    return new_node;
}

void ll_append(ll_ *ll, void *data){
    if (ll->head == NULL){
        ll->head = ll_create_node(data);
        return;
    }
    ll_node *curr = ll->head;
    while (curr->next != NULL){
        curr = curr->next;
    }   
    curr->next = ll_create_node(data);
}

void *ll_pop_front(ll_ *ll){
    ll_node *popped = ll->head;
    ll->head = popped->next;
    return popped->data;
}

void *ll_peek_front(ll_ *ll){
    ll_node *popped = ll->head;
    if (popped == NULL){
        return NULL;
    }
    return popped->data;
}

void *ll_pop_end(ll_ *ll){
    if (ll->head == NULL){
        return NULL;
    }
    if (ll->head->next == NULL){
        void *ret = ll->head->data;
        ll->head = NULL;
        return ret;
    }
    ll_node *prev = ll->head;
    ll_node *curr = ll->head;
    while(curr->next != NULL){
        prev = curr;
        curr = curr->next;
    }
    prev->next = NULL;
    return curr->data;
}

void *ll_peek_end(ll_ *ll){
    if (ll->head == NULL){
        return NULL;
    }
    ll_node *curr = ll->head;
    while(curr->next != NULL){
        curr = curr->next;
    }
    return curr->data;
}

void ll_print(ll_ *ll){
    ll_node *curr = ll->head;
    do {
        printf("%d\n", curr->data);
        curr = curr->next;
    }
    while (curr != NULL);
}

ll_iterator *ll_get_iterator(ll_ *ll){
    ll_iterator *new_ll_it = (ll_iterator *)malloc(sizeof(ll_iterator));
    new_ll_it->curr = ll->head;
    return new_ll_it;
}

void *ll_iterator_get(ll_iterator *ll_it){
    if (ll_it->curr == NULL){
        return NULL;
    }
    void *ret = ll_it->curr->data;
    ll_it->curr = ll_it->curr->next;
    return ret;
}


void *ll_iterator_peek(ll_iterator *ll_it){
    if (ll_it->curr == NULL){
        return NULL;
    }
    return ll_it->curr->data;
}
