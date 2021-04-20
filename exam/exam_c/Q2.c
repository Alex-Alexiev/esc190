#include <stdio.h>
#include<stdlib.h>
#include <string.h>

#include "Q2.h"

typedef struct node {
    char *value;
    struct node *next; 
} node; 

typedef struct hash_table {
    node *nodes;
    int size; 
} hash_table; 

node *new_node(char *val){
    node *new = malloc(sizeof(node));
    new->value = val;
    new->next = NULL;
    return new;
}

int hash_str(char *str, int table_size){
    int hash = 0;
    while (*str){
        hash = (hash * 10) + *str++ - '0';
    }
    return hash%table_size;
}

/*
RUNTIME 
this function uses a hashtable with linked list collisions 
strings are hashed and then inserted into the hash table
since the load factor is < 1, because the size of the table is equal 
to the number of strings, the average insertion is O(1) 

worst case n strings will need to be inserted until a collision is found 
where the strings have the same value, therefore the runtime is O(n)*O(1) = O(n)
*/

int repeats(char **strs, int strs_sz){
    hash_table *hash = malloc(sizeof(hash_table));
    hash->size = strs_sz;
    hash->nodes = malloc(sizeof(node)*hash->size);
    for (int i = 0; i < hash->size; i++){
        hash->nodes[i].value = NULL; 
        hash->nodes[i].next = NULL;
    }
    for (int i = 0; i < strs_sz; i++){
        int key = hash_str(strs[i], strs_sz);
        node *new_entry = new_node(strs[i]);
        if (hash->nodes[key].value == NULL){
            hash->nodes[key] = *new_entry;
        } else {
            //if the strings match return 1 since repetition is found 
            if (strcmp(strs[i], hash->nodes[key].value) == 0){
                return 1;
            }
            //otherwise there is a collision because the strings had the same hash
            //can't just insert on the left side, must iterate through the whole
            //linked list to check for string matches, since it could have 
            //gotten pushed to the end 
            node *curr = hash->nodes[key].next; 
            while (curr != NULL){
                if (strcmp(strs[i], curr->value) == 0){
                    return 1;
                }
                curr = curr->next;
            }
            curr = new_entry;
        }
    }
    return 0;
}