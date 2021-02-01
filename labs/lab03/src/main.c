#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>

#include"LinkedList.h"
#include"Util.h"

char *my_strcat(char *dest, char *src){
    char *ret = (char *)malloc(strlen(dest) + strlen(src));
    int last = 0;

    for (int i = 0; i<strlen(dest); i++){
        ret[i] = dest[i];
        last++;
    }
  
    for(int i = 0; i<strlen(src); i++){
        ret[i + last] = src[i];
    }
    return ret; 
}

//return lexicographical comparison 
int my_strcmp_rec(char *str1, char *str2){
    int diff = *str1 - *str2;
    if (*str1 == 0){
        return diff;
    }
    if (diff == 0){
        return my_strcmp_rec(++str1, ++str2);
    }
    return diff;
}

int my_atoi(char *str){
    int ret;
    int len = strlen(str);
    for (int i = 0; i < len; i++){
        int curr = str[i]-'0';
        ret += curr*pow(10, len - 1- i);
    }
    return ret;
}



int main(){
    // printf("%d\n", my_strcmp_rec("alev", "alex"));
    // char *dest = "one";
    // char *src = "twolasdl";
    // char *res = my_strcat(dest, src);
    
    //my_stcmp_rec("alex", "alex");
    //printf("%d\n", my_atoi("123"));

    dsLinkedList_node *na = dsLinkedList_createNode(NULL);
    dsLinkedList_node *nb = dsLinkedList_createNode(NULL);
    dsLinkedList_node *nc = dsLinkedList_createNode(NULL);
    dsLinkedList_node *nd = dsLinkedList_createNode(NULL);
    dsLinkedList_node *ne = dsLinkedList_createNode(NULL);
    dsLinkedList_node *nf = dsLinkedList_createNode(NULL);

    na->next = nb;
    nb->next = nc;
    nc->next = nd;
    nd->next = ne;
    ne->next = nf;
    nf->next = nc;

    printf("%d\n", dsLinkedList_hasCycle(na));
    return 0;
}