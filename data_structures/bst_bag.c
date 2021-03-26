/* FILE bst_bag.c
 *    Implementation of the Bag ADT using a BST.
 * Author: Francois Pitt, March 2012.
 */

/******************************************************************************
 *  Types and Constants.                                                      *
 ******************************************************************************/

#include <stdlib.h>

#include "bag.h"

/* TYPE bst_node_t -- The type of tree nodes used to store elements. */
typedef struct bst_node {
    elem_t elem;
    struct bst_node *left;
    struct bst_node *right;
} bst_node_t;

/* TYPE bag -- Definition of struct bag from the header file. */
struct bag {
    size_t size;
    bst_node_t *root;
    int (*cmp)(elem_t, elem_t);
};

/******************************************************************************
 *  Helper function declarations, with full documentation.                    *
 ******************************************************************************/

/* FUNCTION bst_destroy
 *    Free the memory allocated for the binary tree rooted at a given node.
 * Parameters and preconditions:
 *    root: the root of the tree to free
 * Return value:  none
 * Side-effects:
 *    all the memory allocated for nodes in the subtree rooted at root has been
 *    freed
 */
static void bst_destroy(bst_node_t *root);

/* FUNCTION bst_elems
 *    Fill an array with the elements in a BST, given its root.  Place the
 *    elements in sorted order, starting at the given index, and return the
 *    number of elements copied.
 * Parameters and preconditions:
 *    root: the root of the BST containing the values to be copied
 *    array: the array into which to copy the values
 *    index: the index of array where to copy the first value
 * Return value:
 *    the number of elements copies into array
 * Side-effects:
 *    elements are copied from the BST rooted at root into array
 */
static size_t bst_elems(const bst_node_t *root, elem_t *array, size_t index);

/* FUNCTION bst_contains
 *    Return whether or not a BST contains a certain element, given the root.
 * Parameters and preconditions:
 *    root: the root of the BST to search
 *    elem: the element to search for
 *    cmp != NULL: the comparison function to use for the search
 * Return value:
 *    true if the BST rooted at 'root' contains elem; false otherwise
 * Side-effects:  none
 */
static bool bst_contains(const bst_node_t *root, elem_t elem,
                         int (*cmp)(elem_t, elem_t));

/* FUNCTION bst_insert
 *    Add an element to a BST, given a pointer to its root.
 * Parameters and preconditions:
 *    root: a pointer to the root of the BST into which to insert
 *    elem: the element to insert
 *    cmp != NULL: the comparison function to use to find the insertion point
 * Return value:
 *    true if elem was inserted; false in case of error
 * Side-effects:
 *    memory has been allocated for the new element, and the tree structure has
 *    been adjusted accordingly
 */
static bool bst_insert(bst_node_t **root, elem_t elem,
                       int (*cmp)(elem_t, elem_t));

/* FUNCTION bst_remove
 *    Remove an element from a BST, given a pointer to its root.
 * Parameters and preconditions:
 *    root: a pointer to the root of the BST into which to remove
 *    elem: the element to remove
 *    cmp != NULL: the comparison function to use to find the removal point
 * Return value:
 *    true if elem was removed; false if the element was not there
 * Side-effects:
 *    memory has been freed for the element removed, and the tree structure has
 *    been adjusted accordingly
 */
static bool bst_remove(bst_node_t **root, elem_t elem,
                       int (*cmp)(elem_t, elem_t));

/* FUNCTION bst_remove_min
 *    Remove and return the smallest element in a BST, given a pointer to its
 *    root.
 * Parameters and preconditions:
 *    root: a pointer to the root of the BST
 * Return value:
 *    the smallest element in the BST rooted at 'root'
 * Side-effects:
 *    memory has been freed for the node containing the smallest element, and
 *    the tree structure has been adjusted accordingly.
 */
static elem_t bst_remove_min(bst_node_t **root);

/* FUNCTION bst_node_create
 *    Create a new bst_node.
 * Parameters and preconditions:
 *    e: the element to store in the new node
 * Return value:
 *    pointer to a new node that stores e and whose children are both NULL;
 *    NULL in case of error with memory allocation
 * Side-effects:
 *    memory has been allocated for the new node
 */
static bst_node_t *bst_node_create(elem_t e);

/******************************************************************************
 *  "Public" function definitions -- see header file for documentation.       *
 ******************************************************************************/

bag_t *bag_create(int (*cmp)(elem_t, elem_t))
{
    bag_t *b = malloc(sizeof(bag_t));
    if (b) {
        b->size = 0;
        b->root = NULL;
        b->cmp = cmp;
    }
    return b;
}

void bag_destroy(bag_t *b)
{
    // Recursively free the memory for tree nodes, then free b itself.
    bst_destroy(b->root);
    free(b);
}

size_t bag_size(const bag_t *b)
{
    return b->size;
}

size_t bag_elems(const bag_t *b, elem_t *a)
{
    // Fill up the array recursively, starting at the root.
    return bst_elems(b->root, a, 0);
}

bool bag_contains(const bag_t *b, elem_t e)
{
    // Recursively search for the element, starting at the root.
    return bst_contains(b->root, e, b->cmp);
}

bool bag_insert(bag_t *b, elem_t e)
{
    // Insert the element recursively, starting at the root.
    if (bst_insert(&b->root, e, b->cmp)) {
        b->size++;
        return true;
    } else {
        return false;
    }
}

bool bag_remove(bag_t *b, elem_t e)
{
    // Remove the element recursively, starting at the root.
    if (bst_remove(&b->root, e, b->cmp)) {
        b->size--;
        return true;
    } else {
        return false;
    }
}

/******************************************************************************
 *  Helper function definitions -- see above for documentation.               *
 ******************************************************************************/

void bst_destroy(bst_node_t *root)
{
    if (root) {
        // Standard post-order traversal to free all the memory.
        bst_destroy(root->left);
        bst_destroy(root->right);
        free(root);
    }
}

size_t bst_elems(const bst_node_t *root, elem_t *array, size_t index)
{
    size_t count = 0; /* number of elements copied so far */
    if (root) {
        // Standard in-order traversal, to copy values in sorted order.
        count += bst_elems(root->left, array, index + count);
        // At this point, count many values have been filled in, so store root's
        // element at the next available location, and increment count.
        array[index + count++] = root->elem;
        // Then continue storing values at the next location.
        count += bst_elems(root->right, array, index + count);
    }
    return count;
}

bool bst_contains(const bst_node_t *root, elem_t elem,
                  int (*cmp)(elem_t, elem_t))
{
    if (! root)
        return false;
    else if (cmp(elem, root->elem) < 0)
        return bst_contains(root->left, elem, cmp);
    else if (cmp(elem, root->elem) > 0)
        return bst_contains(root->right, elem, cmp);
    else /* (cmp(elem, root->elem) == 0) */
        return true;
}

bool bst_insert(bst_node_t **root, elem_t elem, int (*cmp)(elem_t, elem_t))
{
    // This function takes a *pointer* to the pointer to the root node, so that
    // we can modify its value directly -- for example, when this is called with
    // argument &b->root, it gets the *address* of the pointer b->root, so that
    // if b->root == NULL, we can change the value of b->root to point to a new
    // node directly from here.
    if (! *root)
        return (*root = bst_node_create(elem));
    else if (cmp(elem, (*root)->elem) < 0)
        return bst_insert(&(*root)->left, elem, cmp);
    else /* (cmp(elem, (*root)->elem) >= 0) */
        return bst_insert(&(*root)->right, elem, cmp);
    // Duplicate values are always inserted in the right subtree.
}

bool bst_remove(bst_node_t **root, elem_t elem, int (*cmp)(elem_t, elem_t))
{
    // This function takes a *pointer* to the pointer to the root node, so that
    // we can modify its value directly -- for example, when this is called with
    // argument &b->root, it gets the *address* of the pointer b->root, so that
    // if b->root->elem == elem and b->root is the only node, we can change the
    // value of b->root to become NULL directly from here.
    if (! *root)
        return false;
    else if (cmp(elem, (*root)->elem) < 0)
        return bst_remove(&(*root)->left, elem, cmp);
    else if (cmp(elem, (*root)->elem) > 0)
        return bst_remove(&(*root)->right, elem, cmp);
    else { /* (cmp(elem, (*root)->elem) == 0) */
        // We've found the value to remove; check if *root has two children.
        if ((*root)->left && (*root)->right) {
            (*root)->elem = bst_remove_min(&(*root)->right);
        } else { /* remove *root */
            bst_node_t *old = *root;
            *root = (*root)->left ? (*root)->left : (*root)->right;
            free(old);
        }
        return true;
    }
}

elem_t bst_remove_min(bst_node_t **root)
{
    // As above, this function takes a pointer to a pointer to the root node, so
    // that the value of the pointer can be modified directly from in here.
    if ((*root)->left) {
        /* *root is not the minimum, keep going */
        return bst_remove_min(&(*root)->left);
    } else {
        /* remove *root */
        bst_node_t *old = *root;
        elem_t min = (*root)->elem;
        *root = (*root)->right;
        free(old);
        return min;
    }
}

bst_node_t *bst_node_create(elem_t e)
{
    bst_node_t *node = malloc(sizeof(bst_node_t));
    if (node) {
        node->elem = e;
        node->left = NULL;
        node->right = NULL;
    }
    return node;
}
