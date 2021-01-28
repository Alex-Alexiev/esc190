#ifndef LINKEDLIST_H_
#define LINKEDLIST_H_

typedef struct node node;

node *createNode(void *data);

void insert(node *head, void *data);

void append(node *head, void *data);

void printList(node *head,  char *(*stringer)(void *));

void printListRec(node *curr, char *(*stringer)(void *));

#endif