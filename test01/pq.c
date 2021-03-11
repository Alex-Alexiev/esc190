////////////////////////////////////////////////////////////////////////////////
//  As usual, I will use // for comments that explain what I am doing but     //
//  that would not normally belong in well-written code, and I will use the   //
//  more "traditional" delimited comments /*...*/ for "regular" comments.     //
////////////////////////////////////////////////////////////////////////////////

/* FILE min_pq.c
 *    Implementation of the Minimum Priority Queue ADT using a dynamic min-heap
 *    (whose size grows or shrinks to accommodate the number of elements).
 * Author: Francois Pitt, March 2012.
 */
#include <stdio.h>
#include <stdlib.h>

#include "min_pq.h"

/******************************************************************************
 *  Constants, macros, and types.                                             *
 ******************************************************************************/

#define MIN_CAPACITY 4 /* minimum capacity for the heap array */

/* Macros to navigate a heap array's tree structure. */
#define PARENT(node)      ((node) / 2)     /* the index of node's parent      */
#define LEFT_CHILD(node)  ((node) * 2)     /* the index of node's left child  */
#define RIGHT_CHILD(node) ((node) * 2 + 1) /* the index of node's right child */
////////////////////////////////////////////////////////////////////////////////
//  Macros are a bit like preprocessor constants, except instead of using     //
//  them to give names to constant *values*, we use them to give names to     //
//  constant *expressions*.  A macro looks a bit like a function, but it is   //
//  very different: macros are substituted textually in the code *before*     //
//  the code is actually compiled -- in the same way that constants are       //
//  substituted.                                                              //
//  For example, with the definitions above, everywhere in the code that      //
//  'PARENT(expr)' appears, it will be replaced textually by '((expr) / 2)'   //
//  before the code is compiled -- whatever 'expr' may be.  This is why we    //
//  use extra parentheses!                                                    //
//  To make this clear, suppose we have the macro:                            //
//      #define VAL(n) n * 2                                                  //
//  Then the statement:                                                       //
//      if (x / VAL(x+1) > 0)                                                 //
//  becomes:                                                                  //
//      if (x / x+1 * 2 > 0)                                                  //
//  and this is evaluated by C as:                                            //
//      if ((x / x) + (1 * 2) > 0)                                            //
//  This is quire different from the impression given by the original code:   //
//      if (x / VAL(x+1) > 0)                                                 //
//  But if we add parentheses around the parameter and also around the final  //
//  value (since it contains an operator):                                    //
//      #define VAL(n) ((n) * 2)                                              //
//  we get that the statement:                                                //
//      if (x / VAL(x+1) > 0)                                                 //
//  becomes:                                                                  //
//      if (x / ((x+1) * 2) > 0)                                              //
//  and this is exactly what we expected from the original code.              //
////////////////////////////////////////////////////////////////////////////////

/* TYPE item_t -- The type of each heap item. */
typedef struct heap_item {
    const void *element; /* an element in the priority queue         */
    priority_t priority; /* the priority associated with this element*/
} item_t;

/* STRUCT min_pq -- Definition of struct min_pq from the header file. */
struct min_pq {
    size_t size;     /* current size of the priority queue                 */
    size_t capacity; /* capacity of the heap array, always >= MIN_CAPACITY */
    item_t *heap;    /* heap array, allocated dynamically                  */
};

/* TYPE node_t -- The integer type used to represent heap nodes (indices). */
typedef size_t node_t;
////////////////////////////////////////////////////////////////////////////////
//  This helps to make it clearer when we are working with integers that      //
//  represent nodes in a heap.                                                //
////////////////////////////////////////////////////////////////////////////////

/******************************************************************************
 *  Declarations for helper functions -- see below for definitions.           *
 ******************************************************************************/

////////////////////////////////////////////////////////////////////////////////
//  Skip over this at first reading: the need for helper functions becomes    //
//  apparent only while we are writing code, so you need to look at the code  //
//  for each function below to see why we use these helpers.                  //
////////////////////////////////////////////////////////////////////////////////

/* FUNCTION update_capacity
 *    Compare the size of the heap array for a priority queue to its capacity:
 *    if the size (adding one for the unused index 0) is equal to the capacity,
 *    double the capacity; if the size is equal to one quarter of the capacity,
 *    halve the capacity.
 *    To be called *before* inserting or removing a value from the heap.
 * Parameters and preconditions:
 *    q != NULL: a min_pq
 * Return value:  none
 * Side-effects:
 *    the capacity of the heap array has been adjusted as described above;
 *    terminates the program in case of error with memory allocation
 */
static void update_capacity(min_pq_t *q);

/* FUNCTION percolate_up
 *    Percolate "up" the element at a given node in a heap.
 * Parameters and preconditions:
 *    heap != NULL: a heap array, stored starting at index 1
 *    node > 0: the index of a node in heap
 * Return value:  none
 * Side-effects:
 *    values are rearranged to "percolate up" the value at 'node' to restore
 *    heap order (based on the priority values of each heap element)
 */
static void percolate_up(item_t *heap, node_t node);

/* FUNCTION percolate_down
 *    Percolate "down" the element at the root of a heap of given size.
 * Parameters and preconditions:
 *    heap != NULL: a heap array, stored starting at index 1
 *    size > 0: the number of items in heap
 * Return value:  none
 * Side-effects:
 *    values are rearranged to "percolate down" the root to restore heap order
 *    (based on the priority values of each heap element)
 */
static void percolate_down(item_t *heap, size_t size);

/* FUNCTION min_child
 *    Return the index of the child with the lowest priority for a given node in
 *    a min-heap (or a value > size if node has no children).
 * Parameters and preconditions:
 *    heap != NULL: a heap array, stored starting at index 1
 *    node > 0: the index of a node in heap
 *    size > 0: the number of items in heap
 * Return value:
 *    the index of the minimum priority child of node, or an index > size if
 *    node does not have any children
 * Side-effects:  none
 */
static node_t min_child(const item_t *heap, node_t node, size_t size);
////////////////////////////////////////////////////////////////////////////////
//  We don't really "need" a helper function like min_child -- we could just  //
//  compute the required information directly within percolate_down.  But     //
//  having the separate helper function makes the code for percolate_down     //
//  much simpler to write -- and this highlights the similarities between     //
//  percolate_up and percolate_down.                                          //
//  This is enough of an advantage (you'll see when we write the code for     //
//  both "percolate" functions further below) that I would consider it a      //
//  poorer design to leave out this function -- not *much* poorer, though.    //
////////////////////////////////////////////////////////////////////////////////

/* FUNCTION heap_swap
 *    Swap two elements in a heap array.
 * Parameters and preconditions:
 *    heap != NULL: a heap array
 *    i, j: valid indices into heap
 * Return value:  none
 * Side-effects:
 *    the values heap[i], heap[j] have been swapped, in-place
 */
static void heap_swap(item_t *heap, node_t i, node_t j);
////////////////////////////////////////////////////////////////////////////////
//  The next helper function could be left out without really making the      //
//  code less "clean" in terms of design.  But it does represent a single     //
//  well-defined task that needs to be carried out in a few places.  I would  //
//  consider it more a matter of personal preference whether or not to        //
//  include this helper function.                                             //
////////////////////////////////////////////////////////////////////////////////

/******************************************************************************
 *  Definitions for "public" functions -- see .h file for documentation.      *
 ******************************************************************************/

min_pq_t *min_pq_create(void)
{
    min_pq_t *q = malloc(sizeof(struct min_pq));
    if (q) {
        q->size = 0;
        q->capacity = MIN_CAPACITY;
        q->heap = malloc(q->capacity * sizeof(item_t));
        // If the second malloc fails, we cannot use this.
        if (! q->heap) { free(q); q = NULL; }
    }
    return q;
}

void min_pq_destroy(min_pq_t *q)
{
    free(q->heap);
    free(q);
}

size_t min_pq_size(const min_pq_t *q)
{
    return q->size;
}

void min_pq_insert(min_pq_t *q, const void *e, priority_t p)
{
    /* First, make sure the heap array is big enough to add a new item. */
    update_capacity(q);
    /* Next, add the new element with its priority at the end of the heap. */
    q->size++;
    q->heap[q->size].element = e;
    q->heap[q->size].priority = p;
    /* Finally, fix the heap ordering. */
    percolate_up(q->heap, q->size);
}

const void *min_pq_get_min(const min_pq_t *q)
{
    if (min_pq_size(q) == 0)  return NULL;
    return q->heap[1].element;
}

const void *min_pq_remove_min(min_pq_t *q)
{
    if (min_pq_size(q) == 0)  return NULL;
    /* First, make sure the heap array is not too empty. */
    update_capacity(q);
    /* Next, swap the last heap item with the root -- this saves the old root
     * item at the same time as copying the last item into the root. */
    heap_swap(q->heap, 1, q->size--);
    /* Finally, fix the heap ordering. */
    percolate_down(q->heap, q->size);
    /* The element to return is now just past the last item in the heap. */
    return q->heap[q->size + 1].element;
}

/******************************************************************************
 *  Definitions for helper functions -- see above for documentation.          *
 ******************************************************************************/

void update_capacity(min_pq_t *q)
{
    size_t old_cap = q->capacity;
    
    /* Add 1 to the size to account for the unused element at index 0. */
    if (q->size + 1 == q->capacity)
        q->capacity *= 2;
    else if (q->size + 1 == q->capacity / 4 && q->capacity >= 2 * MIN_CAPACITY)
        q->capacity /= 2;
    
    if (q->capacity != old_cap) {
        q->heap = realloc(q->heap, q->capacity * sizeof(item_t));
        // There are other ways to handle this, but it is so unlikely to happen
        // anyway that we won't bother making it more complicated...
        if (q->heap == NULL) {
            perror("ERROR: memory allocation failed");
            exit(EXIT_FAILURE);
        }
    }
}

void percolate_up(item_t *heap, node_t node)
{
    node_t parent = PARENT(node);
    // Using a separate variable to keep track of the parent makes the structure
    // of percolate_up more similar to that of percolate_down.
    
    /* Repeatedly swap node with its parent, as long as node has a parent whose
     * priority is greater than that of node. */
    while (parent >= 1 && heap[parent].priority > heap[node].priority) {
        heap_swap(heap, node, parent);
        node = parent;
        parent = PARENT(node);
    }
}

void percolate_down(item_t *heap, size_t size)
{
    node_t node = 1; /* start at the root */
    node_t child = min_child(heap, node, size);
    
    /* Repeatedly swap node with its child of smallest priority, as long as node
     * has a child whose priority is smaller than that of node. */
    while (child <= size && heap[child].priority < heap[node].priority) {
        heap_swap(heap, node, child);
        node = child;
        child = min_child(heap, node, size);
    }
}

node_t min_child(const item_t *heap, node_t node, size_t size)
{
    node_t left_child = LEFT_CHILD(node);
    node_t right_child = RIGHT_CHILD(node);
    
    // It may seem that multiple cases need to be considered:
    //    (1) when node has no child,
    //    (2) when node has only a left child,
    //    (3) when node has two children.
    // But these cases all roll into a few simple tests.
    //    (1) If node has no child, then right_child > left_child > size, so
    //        it is acceptable to return left_size.
    //    (2) If node has only a left child, then right_child > size and we
    //        simply return left_child.
    // So both these cases are covered by simply testing if right_child > size.
    // For the third case, if right_child <= size, then we compare the
    // priorities of left_child and right_child and return the one with the
    // smallest priority.
    if (right_child > size
             || heap[left_child].priority <= heap[right_child].priority)
        return left_child;
    else
        return right_child;
}

void heap_swap(item_t *heap, node_t i, node_t j)
{
    item_t temp = heap[i];
    heap[i] = heap[j];
    heap[j] = temp;
}