#include <stdio.h>
#include <stdlib.h>
#include <string.h> 

char *alignText(char *inStrings[], int lineLength){
    int runningLength = 0;
    char *curr = inStrings[0];
    char *ret = (char *)malloc(300);
    strcpy(ret, "");
    int ret_i = 0;
    while(strcmp(curr, ".") != 0){
        int currLen = strlen(curr);
        ret_i++;
        if (runningLength + currLen > lineLength){
            runningLength = 0;
            strcat(ret, "\n");
        }
        strcat(ret, curr);
        runningLength += currLen;
        curr = inStrings[ret_i];
    }
    return ret;
}

void swap(char *a, char *b){
    char temp = *a;
    *a = *b;
    *b = temp;
}

void permutate(char *str, int l, int r){
    if (l == r){
        printf("%s\n", str);
    }
    for (int i = l; i <= r; i++){
        swap(str+l, str+i);
        permutate(str, l+1, r);
        swap(str+l, str+i);
    }
}

int is_overflow(int n){
    
}


int main(){
    // char *ins[] = {"This", " is", " my", " example", " for", " the", " exam", " question", "."};
    // char *aligned = alignText(ins, 15);
    // printf("%s\n", aligned);
    char *hi = malloc(10);
    strcpy(hi, "abc");
    permutate(hi, 0, 2);
}