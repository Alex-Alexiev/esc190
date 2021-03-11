#include <stdio.h>
#include <stdlib.h>
#include "intset.h"

int main(void)
{
    printf("Test code for intset\n");
    struct intset *s1;
    struct intset *s2;
    struct intset *s3;
    intset_create(&s1);
    intset_create(&s2);
    
    // Add the elements 5, 4, 4, 10, 4 to s1
    int to_addA[5] = {5, 4, 4, 10, 4};
    int to_addB[4] = {2, 2, 3, 4};
    int to_addC[2] = {10, 12};
    
    intset_add(s1, to_addA, 5); // Add the 5 elements from to_addA to the set s1.
                                // Ignore repetitions
    
    intset_add(s1, to_addC, 2); // Add the 2 elements from to_add
                                // Ignore repetitions
    
    intset_add(s2, to_addB, 3); // Add 2, 2, and 3 to s2. Ignore repetitions.

    
    intset_union(s1, s2, &s3); // Compute the union of the sets
                                      // s1 and s2, and put the result in s3


    printf("Is 2 in s1? %d\n", intset_iselem(s1, 2)); // 0
    printf("Is 3 in s2? %d\n", intset_iselem(s2, 3)); // 1
    printf("Is 4 in s3? %d\n", intset_iselem(s3, 4)); // 1

    intset_remove(s1, 4);      // Remove the element 4 for the set
    printf("Is 4 in s1? %d\n", intset_iselem(s1, 4)); // 0

}