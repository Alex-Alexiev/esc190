#include <stdio.h>
#include <stdlib.h>
#include <string.h>


int my_strlen(char *s1){
    int len = 0;
    while (*s1 != NULL){
        len++;
        s1++; 
    }
    return len;
}

void my_strcpy(char *dest, char *src){
    while(*src != NULL){
        *dest++ = *src++;
        // src++;
        // dest++;
    }
}

int main(){
    char c1 = 'a';
    char c2 = 'A';

    char *s1 = "hellothere"; //c might not put this in an area of memory that is changeable 

    char *s2 = (char *)malloc(sizeof(char)*20);
    s2[0] = 'A';

    char s3[20];

    //['a', 'b', 'c', NULL]
    char s4[4] = "abc";

    printf("%s\n", s4);
    

    char s5[20] = "abc";
    char s6[20];
    strcpy(s6, s5); //copy s5 to s6
    //s6 = s5;// is an error since array is unmodifiable value 

    // int *ia1 = (int *)malloc(sizeof(int)*2);
    // ia1[0] = 1, ia1[1] = 2;
    // int *ia2 = (int *)malloc(sizeof(int)*2);
    // ia2[0] = 3, ia2[1] = 4;
    // ia1 = ia2; //this is valid because its just a pointer

    strlen(s5); //the length of s5 (number of non NULL characters)
    strcmp(s5, s6); // <0 if s5 comes before s6 in lexigraphic ordering, 0 if same, >0 if s5 is after s6 

    return 0;
}