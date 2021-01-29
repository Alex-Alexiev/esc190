#ifndef LINKEDLIST_H_
#define LINKEDLIST_H_

typedef struct node node;

node *llCreateNode(void *data);

void llInsert(node *head, void *data);

void llAppend(node *head, void *data);

void llPrint(node *head,  char *(*stringer)(void *));

void llPrintRec(node *curr, char *(*stringer)(void *));

void llFree(node *curr);

#endif