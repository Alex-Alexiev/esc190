#include<stdio.h>
#include<stdlib.h>

int my_strncmp(char *str1, char *str2, int num){
    if (num == 0){
        return 0;
    }
    char c1 = str1[0];
    char c2 = str2[0];
    if (c1 == '\0'){
        if (c2 == '\0'){
            return 0;
        }
        return -1;
    }
    if (c2 == '\0'){
        if (c1 == '\0'){
            return 0;
        }
        return 1;
    }
    if (c1 == c2){
        return my_strncmp(str1+1, str2+1, num-1);
    }
    return c1-c2;
}

// int main(){
//     printf("%d", my_strncmp("abcde", "abcd", 5));
// }