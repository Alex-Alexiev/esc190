#include <stdio.h>
#include <stdlib.h>

#include "linked_list.h"

typedef struct graph_vertex{
    ll_ *connections;
    void *data; 
    int visited;
} graph_vertex;

typedef struct graph_connection{
    int weight;     
    graph_vertex *v;
} graph_connection; 

typedef struct graph_ {
    ll_ *V;
} graph_;

graph_ *graph_create_graph(){
    ll_ *new_vertex_list = ll_create();
    graph_ *new_graph = (graph_ *)malloc(sizeof(graph_));
    new_graph->V = new_vertex_list;
    return new_graph;
}   

graph_vertex *graph_create_vertex(void *data){
    graph_vertex *new_vertex = (graph_vertex *)malloc(sizeof(graph_vertex));
    ll_ *new_connection_list = ll_create();
    new_vertex->connections = new_connection_list;
    new_vertex->data = data;
    new_vertex->visited = 0;
    return new_vertex;
}

graph_connection *graph_create_connection(int weight, graph_vertex *v){
    graph_connection *new_connection = (graph_connection *)malloc(sizeof(graph_connection));
    new_connection->weight = weight;
    new_connection->v = v;
    return new_connection;
}

void graph_add_vertex(graph_ *g, graph_vertex *v){
    ll_append(g->V, v);
}

void graph_add_connection(graph_vertex *v1, graph_vertex *v2, int weight){
    ll_append(v1->connections, graph_create_connection(weight, v2));
    ll_append(v2->connections, graph_create_connection(weight, v1));
}

void graph_bfs(graph_ *g, void (*callback)(graph_vertex *)){
    ll_ *q = ll_create();
    ll_append(q, ll_peek_front(g->V));

    graph_vertex *curr = NULL;
    graph_connection *conn = NULL;
    ll_iterator *conn_iterator = NULL;

    while (ll_peek_front(q) != NULL){
        curr = (graph_vertex *)ll_pop_front(q);
        (*callback)(curr);
        curr->visited = 1;
        conn_iterator = ll_get_iterator(curr->connections);
        while(ll_iterator_peek(conn_iterator) != NULL){
            conn = ll_iterator_get(conn_iterator);
            if (conn->v->visited == 0){
                ll_append(q, conn->v);
            }
        }
    }
}

void graph_unvisit_all(graph_ *g){
    ll_ *q = ll_create();
    ll_append(q, ll_peek_front(g->V));

    graph_vertex *curr = NULL;
    graph_connection *conn = NULL;
    ll_iterator *conn_iterator = NULL;

    while (ll_peek_front(q) != NULL){
        curr = (graph_vertex *)ll_pop_front(q);
        curr->visited = 0;
        conn_iterator = ll_get_iterator(curr->connections);
        while(ll_iterator_peek(conn_iterator) != NULL){
            conn = ll_iterator_get(conn_iterator);
            if (conn->v->visited == 1){
                ll_append(q, conn->v);
            }
        }
    }
}

void graph_print_vertex_char(graph_vertex *v){
    printf("%c\n", *(char *)(v->data));
}

void graph_dfs_rec(graph_ *g, void (*callback)(graph_vertex *)){
    graph_dfs_helper(ll_peek_front(g->V), callback);
}

void graph_dfs_helper(graph_vertex *v, void (*callback)(graph_vertex *)){
    v->visited = 1;
    (*callback)(v);
    ll_iterator *conn_iterator = ll_get_iterator(v->connections);
    graph_connection *conn = NULL;
    while((conn = ll_iterator_get(conn_iterator)) != NULL){
        if (conn->v->visited == 1){
            continue;
        }
        graph_dfs_helper(conn->v, callback);
    }    
}

void graph_dfs_nonrec(graph_ *g, void (*callback)(graph_vertex *)){
    ll_ *q = ll_create();
    ll_append(q, ll_peek_front(g->V));

    graph_vertex *curr = NULL;
    graph_connection *conn = NULL;
    ll_iterator *conn_iterator = NULL;

    while (ll_peek_end(q) != NULL){
        curr = (graph_vertex *)ll_pop_end(q);
        (*callback)(curr);
        curr->visited = 1;
        conn_iterator = ll_get_iterator(curr->connections);
        while(ll_iterator_peek(conn_iterator) != NULL){
            conn = ll_iterator_get(conn_iterator);
            if (conn->v->visited == 0){
                ll_append(q, conn->v);
            }
        }
    }
}






