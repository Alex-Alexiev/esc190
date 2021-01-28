#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "LinkedList.h"



char *intStringer(void *val){
    int intVal = *(int *)val;
    char *ret = (char *)malloc(sizeof(char)*log10(intVal < 0 ? -intVal*10 : intVal + 1));
    sprintf(ret, "%d", *(int *)val);
    return ret;
}

char *floatStringer(void *val){
    char *ret = (char *)malloc(sizeof(char) * 50);
    sprintf(ret, "%f", *(float *)val);
    return ret;
}

char *doubleStringer(void *val){
    char *ret = (char *)malloc(sizeof(char) * 50);
    sprintf(ret, "%lf", *(double *)val);
    return ret;
}

int main(){

    double a = 3.5, b = 4.5, c = 5.5;
    node *list = createNode(&a);
    append(list, &b);
    append(list, &c);

    printList(list, doubleStringer);
    //printListRec(list);

    return 0;
}