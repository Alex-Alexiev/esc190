#include <stdio.h>
#include <stdlib.h>
#include <math.h>

char *utStringer_int(void *val){
    int intVal = *(int *)val;
    char *ret = (char *)malloc(sizeof(char)*log10(intVal < 0 ? -intVal*10 : intVal + 1));
    sprintf(ret, "%d", *(int *)val);
    return ret;
}

char *utStringer_float(void *val){
    char *ret = (char *)malloc(sizeof(char) * 50);
    sprintf(ret, "%f", *(float *)val);
    return ret;
}

char *utStringer_double(void *val){
    char *ret = (char *)malloc(sizeof(char) * 50);
    sprintf(ret, "%lf", *(double *)val);
    return ret;
}
