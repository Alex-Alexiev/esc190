/*
bag is like a set with repetitions 

bst is implemented here using the bag ADT 

*/




/* FILE main.c
 *    Test the functionality of the bst_bag implementation.
 * Author: Francois Pitt, March 2012.
 */

/******************************************************************************
 *  Types and Constants.                                                      *
 ******************************************************************************/

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#include "bag.h"

/******************************************************************************
 *  Function declarations, including full documentation.                      *
 ******************************************************************************/

/* FUNCTION main
 *    Run some tests of the functionality of the bst_bag implementation.
 * Parameters and preconditions:  none
 * Return value:  exit status
 * Side-effects:  the main program is executed
 */
int main(void);

/* FUNCTION float_cmp
 *    Compare two (void *) values that point to floats and return -1, 0, or +1
 *    as to the first value is less than, equal to, or greater than the second.
 * Parameters and preconditions:
 *    a != NULL: pointer to the first float to compare
 *    b != NULL: pointer to the second float to compare
 * Return value:
 *    -1 if *a < *b; 1 if *a > *b; 0 if *a == *b
 * Side-effects:  none
 */
static int float_cmp(const void *a, const void *b);

/* FUNCTION print_bag
 *    Print all the elements in a bag, in sorted order (as a list), along with
 *    the size of the bag.
 * Parameters and preconditions:
 *    b != NULL: a bag implemented with a BST
 * Return value:  none
 * Side-effects:
 *    the size and contents of b are printed to stdout
 */
static void print_bag(const bag_t *b);

/******************************************************************************
 *  Function definitions -- see above for documentation.                      *
 ******************************************************************************/

int main(void)
{
    size_t i;
    float elts[] = {3.2, 3.1, 3, 10, 11, 4, 1, 0, 0.2, 5, 0.4, 2};
    float bad_elts[] = {56, 0.001, 0.2000001, 75, 50, -1, 0.1};
    
    /* Create a new bag. */
    bag_t *b1 = bag_create(float_cmp);
    
    /* Try to remove something from an empty bag. */
    assert(! bag_remove(b1, &elts[0]));
    
    /* Check that the bag is really empty. */
    printf("Empty bag:\n");
    print_bag(b1);
    printf("An empty bag %s contain %g.\n",
           bag_contains(b1, &elts[0]) ? "does" : "does not", elts[0]);
    
    /* Check that we can insert values into it. */
    for (i = 0; i < sizeof(elts) / sizeof(elts[0]); ++i) {
        assert(bag_insert(b1, &elts[i]));
        printf("After inserting %g:\n", elts[i]);
        print_bag(b1);
        assert(bag_contains(b1, &elts[i]));
        assert(bag_size(b1) == i + 1);
    }
    
    /* See if anything got lost. */
    printf("Lost any element?  ");
    for (i = 0; i < sizeof(elts) / sizeof(elts[0]); ++i) {
        assert(bag_contains(b1, &elts[i]));
    }
    printf("No!\n");
    
    /* See if the bag contains anything it's not supposed to. */
    printf("Any extra elements in there?  ");
    for (i = 0; i < sizeof(bad_elts) / sizeof(bad_elts[0]); ++i)
    {
        assert(! bag_contains(b1, &bad_elts[i]));
    }
    printf("No!\n");
    
    /* Try to insert things twice. */
    printf("Can we insert elements twice?  ");
    for (i = 0; i < sizeof(elts) / sizeof(elts[0]); ++i) {
        assert(bag_insert(b1, &elts[i]));
        assert(bag_size(b1) == i + 1 + sizeof(elts) / sizeof(elts[0]));
    }
    printf("Yes!\n");
    
    /* Try to remove non-existent elements: should have no effect. */
    printf("Can we remove non-existent elements?  ");
    for (i = 0; i < sizeof(bad_elts) / sizeof(elts[0]); ++i) {
        assert(! bag_remove(b1, &bad_elts[i]));
        assert(bag_size(b1) == 2 * sizeof(elts) / sizeof(elts[0]));
    }
    printf("No!\n");
    
    /* Make sure duplicate elements can be removed. */
    for (i = 0; i < sizeof(elts) / sizeof(elts[0]); ++i) {
        assert(bag_remove(b1, &elts[i]));
        printf("After removing %g:\n", elts[i]);
        print_bag(b1);
        assert(bag_contains(b1, &elts[i]));
        assert(bag_size(b1) == 2 * sizeof(elts) / sizeof(elts[0]) - i - 1);
    }
    
    /* Make sure elements can be removed. */
    for (i = 0; i < sizeof(elts) / sizeof(elts[0]); ++i) {
        assert(bag_remove(b1, &elts[i]));
        printf("After removing %g:\n", elts[i]);
        print_bag(b1);
        assert(! bag_contains(b1, &elts[i]));
        assert(bag_size(b1) == sizeof(elts) / sizeof(elts[0]) - i - 1);
    }
    
    /* Clean up... */
    bag_destroy(b1);
    
    return EXIT_SUCCESS;
}

int float_cmp(const void *a, const void *b)
{
    return *(float *) a < *(float *) b ? -1
         : *(float *) a > *(float *) b; /* ? 1 : 0 redundant */
}

static void print_bag(const bag_t *b)
{
    elem_t *elems;
    size_t i;
    
    printf("    size: %lu\n", bag_size(b));
    printf("    contents: [");
    if (bag_size(b) > 0) {
        elems = malloc(bag_size(b) * sizeof(elem_t));
        bag_elems(b, elems);
        printf("%g", *(float *) elems[0]);
        for (i = 1; i < bag_size(b); ++i)  printf(", %g", *(float *) elems[i]);
        free(elems);
    }
    printf("]\n");
}
