#ifndef LINKEDLIST_H_
#define LINKEDLIST_H_

typedef struct dsLinkedList_node{
    void *data;
    struct dsLinkedList_node *next; 
} dsLinkedList_node;

dsLinkedList_node *dsLinkedList_createNode(void *data);

void dsLinkedList_insert(dsLinkedList_node *head, void *data);

void dsLinkedList_append(dsLinkedList_node *head, void *data);

void dsLinkedList_print(dsLinkedList_node *head,  char *(*stringer)(void *));

void dsLinkedList_printRec(dsLinkedList_node *curr, char *(*stringer)(void *));

void dsLinkedList_free(dsLinkedList_node *curr);

int dsLinkedList_hasCycle(dsLinkedList_node *head);

#endif