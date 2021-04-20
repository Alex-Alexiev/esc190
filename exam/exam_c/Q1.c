#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "Q1.h"

char *concat_all(char *strs[], int num){
    int total_len = 0;
    for (int i = 0; i < num; i++){
        total_len += strlen(strs[i]);
    }
    char *ret = malloc(total_len+1);
    strcpy(ret, "");
    for (int i = 0; i < num; i++){
        strcat(ret, strs[i]);
    }
    return ret;
}
