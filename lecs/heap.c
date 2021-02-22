#include <stdio.h>
#include <stdlib.h>

//priority queue - first elemtn dequed is the one with the highes tpriority 

//uses: 
//simulate real-world systems queses organized by priority - patients in hospital, files from server
//A* search 

//insert(S, x): add a new elemtn with priroty x to quee S
//min(S): return the element with the smallest value

//array, linked list - O(1) for insertion, O(n) for min 
//sorted array/linked list - O(n) for insert, O(1) for min 

//heaps

//tree - every node having two children except the leaves (at the bottom)
//complete tree - every leaf is as far left as possible on the last level (only the last level can have no children and the missing ones must all be on the right)

//since the tree is complete we can store the heap as an arrya and read level by level 
//given node at index i
//parent(i) = i/2
//left(i) = 2*i
//right(i) = 2*i = 1

//heap order propertyu - for each node n other than the root(top node) in  a binary heap, the value stored in the parent must be less
//than or equal to the value stored in n 

//insert - put at bottom most left spot (first available) then percolate the value up the tree until it is in an appropriate spot 
//percolate - compare with parents and swap if child is smaller than parent 

/*
insert(x){
    k = n + 1;
    pq[k] = x;
    while (k > 1 and pq[k/2] > pq[k]){
        swap(pq[k], pq[k/2])
        k = k/2
    }
}
*/

//extract_min - replace the min elemtn (the one at the top) with the element at the end of the array then percolate it down to its spot 

/*
extract_min(){
    min = pq[1]
    swap(pq[1], pq[n])
    n = n-1
    k = 1
    while (2*k <= n){
        j = 2*k
        if (j < n and pq[j] > pq[j+1]){
            j++ //want to exchange with the smaller child 
        }
        if (pq[k] <= pq[j]){
            break
        }
        swap(pq[k], pq[j])
        k = j
    }
    return min
}
*/


//complexity - n <= 2^h+1 - 1 //h is height of tree 
//log2n < h+1
//insert and extract_min need at most h swaps so O(h) = O(log(n))


int main(){
    
    return 0;
}