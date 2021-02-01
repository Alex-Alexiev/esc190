#include <stdio.h>
#include <stdlib.h>

#include "LinkedList.h"

dsLinkedList_node *dsLinkedList_createNode(void *data){
    dsLinkedList_node *newNode = NULL;
    newNode = (dsLinkedList_node *)malloc(sizeof(dsLinkedList_node));
    if (newNode == NULL){
        printf("unable to create dsLinkedList_node");
        exit(1);
    }
    newNode->data = data;
    newNode->next = NULL;
    return newNode;
}

void dsLinkedList_insert(dsLinkedList_node *head, void *data){
    dsLinkedList_node *newNode = dsLinkedList_createNode(data);
    newNode->next = head->next;
    head->next = newNode;
}

void dsLinkedList_append(dsLinkedList_node *head, void *data){
    while(head->next != NULL){
        head = head->next;
    }
    head->next = dsLinkedList_createNode(data);
}

void dsLinkedList_print(dsLinkedList_node *head, char *(*stringer)(void *)){
    while(head != NULL){
        printf("%s ", (*stringer)(head->data));
        head = head->next;
    }
    printf("\n");
}

void dsLinkedList_printRec(dsLinkedList_node *curr, char*(*stringer)(void *)){
    if (curr == NULL){
        printf("\n");
        return; 
    }
    printf("%s ", (*stringer)(curr->data));
    dsLinkedList_printRec(curr->next, stringer);
}

void dsLinkedList_free(dsLinkedList_node *curr){
    if (curr == NULL){
        return;
    }
    dsLinkedList_free(curr->next);
    free(curr);
}

int dsLinkedList_hasCycle(dsLinkedList_node *head){
    dsLinkedList_node *tortoise = head->next;
    dsLinkedList_node *hare = head->next->next;
    while (tortoise != hare){
        if (hare->next == NULL || hare->next->next == NULL){
            return 0;
        }
        hare = hare->next->next;
        tortoise = tortoise->next;
    }

    int mu = 0;
    tortoise = head;
    while(tortoise != hare){
        tortoise = tortoise->next;
        hare = hare->next;
        mu++;
    }
    /*
    0 - 0 - 0 - 0
            |   |
            0 - 0
    */
    int lam = 1;
    hare = tortoise->next;
    while (tortoise != hare){
        hare = hare->next;
        lam++;
    }
    printf("cycle_start:%d, cycle_length:%d\n", mu, lam);
    return 1;
}

