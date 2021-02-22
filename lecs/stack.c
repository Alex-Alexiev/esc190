#include <stdio.h>
#include <stdlib.h>

typedef struct stack {
    int *data;
    int size; //the size of the data block data 
    int n; //current number of elements
} stack; 


void create_stack(stack *s){
    s->size = 1;
    s->data = (int *)malloc(sizeof(int)*s->size);
    s->n = 0;
}

void push(stack *s, int elem){
    if (s->size == s->n){
        s->data = realloc(s->data, s->size * 2);
        s->size *= 2;
    }
    s->data[s->n] = elem;
    s->n++;
}

int pop(stack *s){
    return s->data[--s->n];
}


int main(){
    
    return 0;
}