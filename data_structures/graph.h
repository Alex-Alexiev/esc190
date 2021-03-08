#ifndef GRAPH_H
#define GRAPH_H

typedef struct graph_ graph_;
typedef struct graph_vertex graph_vertex;
typedef struct graph_connection graph_connection; 

graph_ *graph_create_graph();

graph_vertex *graph_create_vertex(void *data);

graph_connection *graph_create_connection(int weight, graph_vertex *v);

void graph_add_vertex(graph_ *g, graph_vertex *v);

void graph_add_connection(graph_vertex *v1, graph_vertex *v2, int weight);

void graph_bfs_print(graph_ *g, void (*callback));

void graph_print_vertex_char(graph_vertex *v);

void graph_unvisit_all(graph_ *g);


#endif