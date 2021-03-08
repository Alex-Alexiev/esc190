#ifndef LINKED_LIST_H
#define LINKED_LIST_H

typedef struct ll_node ll_node;

typedef struct ll_ ll_;

typedef struct ll_iterator ll_iterator;

ll_ *ll_create();

ll_node *ll_create_node(void *data);

void ll_append(ll_ *ll, void *data);

void ll_print(ll_ *ll);

void *ll_pop_front(ll_ *ll);

void *ll_pop_end(ll_ *ll);

void *ll_peek_front(ll_ *ll);

void *ll_peek_end(ll_ *ll);

ll_iterator *ll_get_iterator(ll_ *ll);

void *ll_iterator_get(ll_iterator *ll_it);

void *ll_iterator_peek(ll_iterator *ll_it);


#endif