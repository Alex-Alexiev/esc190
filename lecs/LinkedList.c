#include <stdio.h>
#include <stdlib.h>

//Linked Lists 
//node
//  node contains data and a pointer to the next element 

//append
//length
//max
//rec_length
//rec_max
//delete 

typedef struct node {
    int data; //in python: void *data, and also store the data type 
    node *next;
} node;

void append(node *head, int value){
    node *curr = head;
    while(curr->next != NULL){
        curr = curr->next;
    }
    node *newNode = (node *)malloc(sizeof(node));
    newNode->data = value;
    newNode->next = NULL;
    curr->next = newNode;
}

void maxList(node *head){
    node *curr = head;
    int maxVal = curr->data;
    while (curr != NULL){
        if (curr->data > maxVal){
            maxVal = curr->data;
        }
        curr = curr->next;
    }
    return maxVal;
}

int maxInt(int a, int b){
    if (a > b){
        return a;
    } else {
        return b;
    }
}

int maxListRecursive(node *head){
    if (head->next == NULL){
        return head->data;
    }
    return maxInt(head->data, maxListRecursive(head->next));
}

int main(){

    node *node0 = (struct node *)malloc(sizeof(node));
    node0->data = 3;

    node *node1 = (struct node *)malloc(sizeof(node));
    node0->next = node1;
    node1->data = 5;
    node1->next = NULL;
    
    return 0;
}