#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>

#include"LinkedList.h"
#include"Util.h"

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

int main(){
    printf("str_cmp: %d\n", my_strcmp_rec("aley", "alez"));

    char *dest = "one";
    char *src = "two";
    char *res = my_strcat(dest, src);

    printf("catentation: %s\n", res);
    
    //my_stcmp_rec("alex", "alex");
    printf("%d\n", my_atoi("123"));

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