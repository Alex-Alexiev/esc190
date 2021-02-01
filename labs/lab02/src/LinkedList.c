#include <stdio.h>
#include <stdlib.h>

#include "LinkedList.h"

typedef struct node{
    void *data;
    node *next; 
} node;

node *llCreateNode(void *data){
    node *newNode = NULL;
    newNode = (node *)malloc(sizeof(node));
    if (newNode == NULL){
        printf("unable to create node");
        exit(1);
    }
    newNode->data = data;
    newNode->next = NULL;
    return newNode;
}

void llInsert(node *head, void *data){
    node *newNode = llCreateNode(data);
    newNode->next = head->next;
    head->next = newNode;
}

void llAppend(node *head, void *data){
    while(head->next != NULL){
        head = head->next;
    }
    head->next = llCreateNode(data);
}

void llPrint(node *head, char *(*stringer)(void *)){
    while(head != NULL){
        printf("%s ", (*stringer)(head->data));
        head = head->next;
    }
    printf("\n");
}

void llPrintRec(node *curr, char*(*stringer)(void *)){
    if (curr == NULL){
        printf("\n");
        return; 
    }
    printf("%s ", (*stringer)(curr->data));
    llPrintRec(curr->next, stringer);
}

void llFree(node *curr){
    if (curr == NULL){
        return;
    }
    llFree(curr->next);
    free(curr);
    // node *next = NULL;
    // while (curr != NULL){
    //     next = curr->next;
    //     free(curr);
    //     curr = next;
    // }
}