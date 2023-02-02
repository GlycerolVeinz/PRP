#include <stdio.h>
#include <stdlib.h>

#include "graph.c"

#define INF 1000000

// void dijkstra(graph_t *g, int start);

int main(int argc, char const *argv[])
{
    graph_t *g = allocate_graph();
    load_txt("in.txt", g);

    printf("Graph of size %d:\n", g->size);
    for (int i = 0; i < g->size; i++) {
        printf("%d -> %d: %d\n", g->edges[i]->from, g->edges[i]->to,g->edges[i]->cost);
    }

    // dijkstra(g, 0);

    free_graph(&g);
    return 0;
}


