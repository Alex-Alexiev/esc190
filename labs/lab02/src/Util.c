#include <stdio.h>
#include <stdlib.h>
#include <math.h>

char *utIntStringer(void *val){
    int intVal = *(int *)val;
    char *ret = (char *)malloc(sizeof(char)*log10(intVal < 0 ? -intVal*10 : intVal + 1));
    sprintf(ret, "%d", *(int *)val);
    return ret;
}

char *utFloatStringer(void *val){
    char *ret = (char *)malloc(sizeof(char) * 50);
    sprintf(ret, "%f", *(float *)val);
    return ret;
}

char *utDoubleStringer(void *val){
    char *ret = (char *)malloc(sizeof(char) * 50);
    sprintf(ret, "%lf", *(double *)val);
    return ret;
}
