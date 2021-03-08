#include<stdio.h>

#include "linked_list.h"
#include "graph.h"



int main(){
    graph_ *g = graph_create_graph();
    char A = 'A';
    char B = 'B';
    char C = 'C';
    char D = 'D';
    graph_vertex *vA = graph_create_vertex(&A);
    graph_vertex *vB = graph_create_vertex(&B);
    graph_vertex *vC = graph_create_vertex(&C);
    graph_vertex *vD = graph_create_vertex(&D);
    graph_add_vertex(g, vA);
    graph_add_vertex(g, vB);
    graph_add_vertex(g, vC);
    graph_add_vertex(g, vD);

    graph_add_connection(vA, vB, 1);
    graph_add_connection(vA, vC, 1);
    graph_add_connection(vB, vD, 1);
    
    
    // graph_bfs(g, graph_print_vertex_char);
    // graph_unvisit_all(g);
    graph_dfs_rec(g, graph_print_vertex_char);
    
    
}