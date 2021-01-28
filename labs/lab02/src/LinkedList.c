#include <stdio.h>
#include <stdlib.h>

#include "LinkedList.h"

typedef struct node{
    void *data; 
    node *next; 
} node;

node *createNode(void *data){
    node *newNode = (node *)malloc(sizeof(node));
    newNode->data = data;
    newNode->next = NULL;
    return newNode;
}

void insert(node *head, void *data){
    node *newNode = createNode(data);
    newNode->next = head->next;
    head->next = newNode;
}

void append(node *head, void *data){
    while(head->next != NULL){
        head = head->next;
    }
    head->next = createNode(data);
}

void printList(node *head, char *(*stringer)(void *)){
    while(head != NULL){
        printf("%s ", (*stringer)(head->data));
        //printf("%s, ", head->data);
        head = head->next;
    }
    printf("\n");
}

void printListRec(node *curr, char*(*stringer)(void *)){
    if (curr == NULL){
        printf("\n");
        return; 
    }
    printf("%s ", (*stringer)(curr->data));
    printListRec(curr->next, stringer);
}