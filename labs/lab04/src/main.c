#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>

#include"LinkedList.h"
#include"Util.h"

int binary_search(int *L, int e, int left, int right){
    if (right >= left){
        size_t mid = left + (right - left)/2;
        if (L[mid] == e){
            return mid;
        }
        if (L[mid] > e){
            return binary_search(L, e, left, mid-1);
        }
        return binary_search(L, e, mid+1, right);
    }
    return -1;
}


int find_first(int *L, int e, int length){
    
    size_t index = binary_search(L, e, 0, length - 1);
    if(index == -1){
        return -1;
    }
    while(index > 0 && L[index-1] == e){
        index--;
    }
    return index;
}

int find_last(int L[], int e, int length){
    size_t index = binary_search(L, e, 0, length - 1);
    if (index == -1){
        return -1;
    }
    while (index < length-1){
        if (L[index + 1] != e){
            return index;
        }
        index++;
    }    
    return -2;
}

int main(){

    int L[5] = {1, 2, 5, 5, 6};


    printf("%d\n", find_last(L, 5, 5));

    // dsLinkedList_node *na = dsLinkedList_createNode(NULL);
    // dsLinkedList_node *nb = dsLinkedList_createNode(NULL);
    // dsLinkedList_node *nc = dsLinkedList_createNode(NULL);
    // dsLinkedList_node *nd = dsLinkedList_createNode(NULL);
    // dsLinkedList_node *ne = dsLinkedList_createNode(NULL);
    // dsLinkedList_node *nf = dsLinkedList_createNode(NULL);

    // na->next = nb;
    // nb->next = nc;
    // nc->next = nd;
    // nd->next = ne;
    // ne->next = nf;
    // nf->next = nc;

    // printf("%d\n", dsLinkedList_hasCycle(na));
    return 0;

    
}