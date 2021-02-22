#include <stdlib.h>

//type of priorities 
typedef long priority_t;

//typenof a min priority queue (smallest value on top)
typedef struct min_pq min_pq_t;

min_pq_t* min_pq_create(min_pq_t *q){

}

size_t min_pq_size(const min_pq_t *q){

}

void min_pq_insert(min_pq_t *q, const void *e, priority_t p){

}

const void *min_pq_get_min(const min_pq_t *q){

}

const void *min_pq_remove_min(min_pq_t *q){

}



#define MIN_CAPACITY 4

#define PARENT(node) ((node)/2)
#define LEFT_CHILD(node) ((node)*2)
#define RIGHT_CHILD(node) ((node)*2 + 1)

typedef struct heap_item {
    const void *element;
    priority_t priority;
} item_t;

struct min_pq {
    size_t size; //current size of pq 
    size_t capacity; //capacity of heap array 
    item_t *heap;
};

typedef size_t node_t; //integer used to represent heap nodes (indicies)

void percolate_up(item_t *heap, node_t node){
    node_t parent = PARENT(node);

    while (parent >= 1 && heap[parent].priority > heap[node].priority){
        heap_swap(heap, node, parent);
        node = parent;
        parent = PARENT(node);
    }
}

void update_capacity(min_pq_t *q){
    size_t old_cap = q->capacity;
    if (q->size + 1 == q->capacity){
        q->capacity *= 2;
    }
}

void min_pq_insert(min_pq_t *q, const void *e, priority_t p){
    update_capacity(q);
}

int main(){

}