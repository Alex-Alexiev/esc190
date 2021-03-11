#include<stdlib.h>
#include<stdio.h>

#include"intset.h"

void intset_remove(struct intset *s, int elem){
    struct node *curr = s->head;
    if (curr == NULL){
        return;
    }
    if (curr->next == NULL){
        if (curr->data == elem){
            s->head = NULL;
        }
        return;
    }
    if (curr->data == elem){
        s->head = curr->next;
    }
    curr = curr->next;
    struct node *prev = s->head;
    while(curr != NULL){
        if (curr->data == elem){
            if (curr->next == NULL){
                prev->next = NULL;
            } else {
                prev->next = curr->next;
            }
        }
        prev = curr;
        curr = curr->next;
    }
}

int intset_iselem(struct intset *s, int elem){
    struct node *curr = s->head;
    while(curr != NULL){
        if (curr->data == elem){
            return 1;
        }
        curr = curr->next;
    }
    return 0;
}

void intset_print(struct intset *s){
    struct node *curr = s->head;
    while(curr != NULL){
        printf("%d, ", curr->data);
        curr = curr->next;
    }
    printf("\n");
}

void intset_create(struct intset **s){
    struct intset *new_intset = (struct intset *)malloc(sizeof(struct intset));
    if (new_intset == NULL){
        exit(EXIT_FAILURE);
    }
    new_intset->head = NULL;
    (*s) = new_intset;
}

struct node *intset_create_node(int elem){
    struct node *new_node = (struct node *)malloc(sizeof(struct node));
    if (new_node == NULL){
        exit(EXIT_FAILURE);
    }
    new_node->next = NULL;
    new_node->data = elem;
    return new_node;
}

void intset_add_single(struct intset *s, int elem){
    if (s->head == NULL){
        s->head = intset_create_node(elem);
        return;
    }
    struct node *curr = s->head;
    while(curr->next != NULL){
        if (curr->data == elem){
            return;
        }
        curr = curr->next;
    }
    if (curr->data == elem){
        return;
    }
    curr->next = intset_create_node(elem);
}

void intset_add(struct intset *s, int *elems, int num_elems){
    for (int i = 0; i < num_elems; i++){
        intset_add_single(s, elems[i]);
    }
}

//add elements of s1 to s2
void intset_add_set(struct intset *s1, struct intset *s2){
    struct node *curr = s1->head;
    while(curr != NULL){
        intset_add_single(s2, curr->data);
        curr = curr->next;
    }
}

void intset_union(struct intset *s1, struct intset *s2, struct intset **s3){
    intset_create(s3);
    intset_add_set(s1, *s3);
    intset_add_set(s2, *s3);
}

