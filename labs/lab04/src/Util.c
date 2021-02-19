#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

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

char *my_strcat(char *dest, char *src){
    char *ret = (char *)malloc(strlen(dest) + strlen(src));

    int i = 0;
    for (; i<strlen(dest); i++){
        ret[i] = dest[i];
    }
  
    for(int j = 0; j <strlen(src); j++){
        ret[i + j] = src[j];
    }
    return ret; 
}

//return lexicographical comparison 
int my_strcmp_rec(char *str1, char *str2){
    if (*str1 == 0 && *str2 == 0){
        return 0;
    }
    if (*str1 == 0){
        return 'a' - *str2;
    }
    if (*str2 == 0){
        return *str1 - 'a';
    }
    
    int diff = *str1 - *str2;
    if (diff == 0){
        return my_strcmp_rec(++str1, ++str2);
    }
    return diff;
}

int my_atoi(char *str){
    int ret = 0;
    int len = strlen(str);
    for (int i = 0; i < len; i++){
        int curr = str[i]-'0';
        ret += curr*pow(10, len - 1- i);
    }
    return ret;
}

