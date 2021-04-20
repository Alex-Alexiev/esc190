#include "hashtable.h"
#include <stdio.h>

int hash_fn(int key, int table_size){
    return key % table_size;
}

int probe_fun(int i, int key){
    return i;
}

int main(void)
{
    struct hashtable *ht;
    ht_create(&ht, 0.8, hash_fn, probe_fun);
    
    ht_set(ht, 212, 20); 
    ht_print(ht);

    printf("212 is in: %d\n", ht_in(ht, 212));
    printf("213 is in: %d\n", ht_in(ht, 213));

    ht_delete(ht, 212);
    printf("212 is in: %d\n", ht_in(ht, 212));
    printf("213 is in: %d\n", ht_in(ht, 213));

    ht_set(ht, 212, 20); 
    printf("212 is in: %d\n", ht_in(ht, 212));
    printf("213 is in: %d\n", ht_in(ht, 213));

    ht_print(ht);

    printf("%d\n", ht_get(ht, 212));
    return 0;
    
    ht_set(ht, 222, 25); 
    ht_print(ht);

    ht_delete(ht, 222); 
    ht_print(ht);

    ht_set(ht, 223, 26); 
    ht_print(ht);
    
    ht_set(ht, 224, 28); 
    ht_set(ht, 226, 29); 
    ht_set(ht, 227, 30); 
    
    ht_set(ht, 228, 31); 
    ht_set(ht, 229, 32); 
    ht_set(ht, 230, 33); 
    ht_set(ht, 231, 34); 
    ht_set(ht, 232, 35); 
    ht_set(ht, 533, 36); 
    ht_set(ht, 534, 37); 
    ht_set(ht, 535, 38); 
    ht_set(ht, 536, 39); 
    ht_set(ht, 537, 40); 
    ht_set(ht, 538, 41); 
    


    ht_print(ht);

    ht_delete(ht, 223);

    ht_destroy(ht);

    return 0;
}