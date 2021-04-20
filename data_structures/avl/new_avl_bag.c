#include <stdio.h>
#include <stdlib.h>

#include "bag.h"

#define HEIGHT(node) ((node) ? (node)->height : 0)

typedef struct avl_node {
    bag_elem_t elem;
    size_t height; 
    struct avl_node *left; 
    struct avl_node *right; 
} avl_node_t;

struct bag{
    avl_node_t *root; 
    size_t size; 
    int (*cmp)(bag_elem_t, bag_elem_t);
}

static
void avl_destroy(avl_node_t *root){
    if(!root){
        return 
    }
    avl_destroy(root->left);
    avl_destroy(root->right);
    free(root)
}

static 
size_t avl_elems(const avl_node_t *root, bag_elem_t *array, size_t index){
    size_t count = 0;
    if (root){
        count += avl_elems(root->left, array, index);
        array[index + count] = root->elem;
        count++;
        avl_elems(root->right, array, index+count);
    }
    return count; 
}

static 
void avl_traverse(const avl_node_t *root, void (*fun)(bag_elem_t)){
    if(root){
        (*fun)(root->elem);
        avl_traverse(root->left, fun);
        avl_traverse(root->right, fun);
    }
}

static 
bool avl_contains(const avl_node_t *root, bag_elem_t elem, int (*cmp)(bag_elem_t, bag_elem_t)){
    if (!root){
        return false; 
    }
    int comp = (*cmp)(elem, root->elem)
    if (comp < 0){
        return avl_contains(root->left, elem, cmp);
    }
    if (comp > 0){
        return avl_contains(root->right, elem, cmp);
    }
    return true; 
}

static 
void avl_insert(avl_node_t **root, bag_elem_t elem, int (*cmp)(bag_elem_t, bag_elem_t)){
    if (!(*root)){
        (*root) = avl_node_create(elem);
        return
    }
    int comp = (*cmp)(elem, (*root)->elem);
    if(comp < 0){
        avl_insert(&((*root)->left), elem, cmp);
    }
    if(comp > 0){
        avl_insert(&((*root)->right), elem, cmp);
    }
    else {
        if (HEIGHT((*root)->left) > HEIGHT((*root)->right)){
            avl_insert(&((*root)->right), elem, cmp);
        } else {
            avl_insert(&((*root)->left), elem, cmp);
        }
    }

    avl_update_height(*root); 
    avl_balance(root);

}

static 
void avl_remove(avl_node_t **root, bag_elem_t elem, int(*cmp)(bag_elem_t, bag_elem_t)){
    if (!(*root)){
        return 
    }
    int comp = (*cmp)(elem, (*root)->elem);
    if (comp < 0){
        avl_remove(&(*root)->left, elem, cmp);
    }
    else if (comp > 0){
        avl_remove(&(*root)->right, elem, cmp);
    } else {
        if ((*root)->left && (*root)->right){
            if (HEIGHT((*root)->left) > HEIGHT((*root)->right)){
                (*root)->elem = avl_remove_max(&(*root)->left);
            } else {
                (*root)->elem = avl_remove_min(&(*root)->right);
            }
        } else {
            avl_node_t *old = (*root); 
            (*root) = old->left ? old->left : old->right;
            free(old);
        }
    }
    avl_update_height(*root);
    avl_balance(root);
}

static 
bag_elem_t avl_remove_max(avl_node_t **root){
    if (!(*root)->right){
        bag_elem_t max = (*root)->elem;
        avl_node_t *old = (*root);
        (*root) = old->left;
        free(old);
        return max; 
    } else {
        bag_elem_t max = avl_remove_max(&(*root)->right); 
        avl_update_height(*root);
        avl_balance(root);
        return max;
    }
}

static 
bag_elem_t avl_remove_min(avl_node_t **root){
    if (!(*root)->left){
        bag_elem_t min = (*root)->elem;
        avl_node_t *old = (*root);
        (*root) = old->right;
        free(old);
        return min; 
    } else {
        bag_elem_t min = avl_remove_min(&(*root)->left); 
        avl_update_height(*root);
        avl_balance(root);
        return min;
    }
}

static 
void avl_balance(avl_node_t **root)){
    if (HEIGHT((*root)->left) - HEIGHT((*root)->right) > 1){
        avl_balance_left(root);
    } else {
        avl_balance_right(root);
    }
}

static 
void avl_balance_left(avl_node_t **root){
    if (HEIGHT((*root)->left->right) > HEIGHT((*root)->left->left)){
        avl_rotate_left(&(*root)->left);
    }
    avl_rotate_right(root);
}

static 
void avl_balance_right(avl_node_t **root){
    if (HEIGHT((*root)->right->left) > HEIGHT((*root)->right->right)){
        avl_rotate_right(&(*root)->right);
    }
    avl_rotate_left(root);
}

static 
void avl_rotate_right(avl_node_t **root){
    avl_node_t *x = (*root);
    avl_node_t *y = x->left;
    avl_node_t *T = y->right;
    x->left = T; 
    y->right = x;
    (*root) = y; 
    avl_update_height(root->right);
    avl_update_height(root);
}

static 
void avl_rotate_left(avl_node_t **root){
    avl_node_t *x = (*root);
    avl_node_t *y = x->right;
    avl_node_t *T = y->left;
    x->right = T; 
    y->left = x;
    (*root) = y; 
    avl_update_height(root->left);
    avl_update_height(root);
}

static 
void avl_update_height(avl_node_t **root){
    (*root)->height = 1 + HEIGHT((*root)->left) > HEIGHT((*root)->right) ? HEIGHT((*root)->left) : HEIGHT((*root)->right);
}

avl_node_t *avl_node_create(bag_elem_t elem){
    avl_node_t *new_node = malloc(sizeof(avl_node_t));
    if (new_node){
        new_node->elem = elem;
        new_node->left = NULL;
        new_node->right = NULL;
        new_node->height = 1; 
    }
    return new_node; 
}