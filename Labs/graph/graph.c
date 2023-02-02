#include "graph.h"
#include <stdio.h>
#include <stdlib.h>

#define INIT_SIZE 10
#define ERR_MALOC 100
#define ERR_FILE 101

void *CheckedMalloc(size_t size)
{
    void *ret = malloc(size);
    if (!ret)
    {
        fprintf(stderr, "Malloc failed!\n");
        exit(ERR_MALOC);
    }
    return ret;
}

void *CheckedRealloc(void *ptr, size_t size)
{
    void *ret = realloc(ptr, size);
    if (!ret)
    {
        fprintf(stderr, "Realloc failed!\n");
        exit(ERR_MALOC);
    }
    return ret;
}

void *CheckedFopen(const char *fname, const char *mode)
{
    // fopen that raises err instead of ret null
    FILE *a_file = fopen(fname, mode);

    if (!a_file)
    {
        fprintf(stderr, "Couldn't open a file!\n");
        exit(ERR_FILE);
    }

    return a_file;
}


/* Allocate a new graph and return a reference to it. */
graph_t* allocate_graph()
{
    graph_t *g = CheckedMalloc(sizeof(graph_t));

    g->capacity = INIT_SIZE;
    g->edges = CheckedMalloc(sizeof(edge_t*));
    g->size = 0;

    return g;
}


/* Free all allocated memory and set reference to the graph to NULL. */
void free_graph(graph_t **graph)
{
    for (int i = 0; i < (*graph)->size; i++)
    {
        free((*graph)->edges[i]);
    }

    free((*graph)->edges);
    (*graph)->size = 0;
    (*graph)->edges = 0;
    (*graph) = NULL;
}

/* Load a graph from the text file. */
void load_txt(const char *fname, graph_t *graph)
{
    FILE *o_file = CheckedFopen(fname, "r");

    edge_t *node = NULL;
    int i = 0;

    while (fscanf(o_file, "%d %d %d", &(*node).from, &(*node).to, &(*node).cost) == 3)
    {
        if (graph->capacity == graph->size)
        {
            graph->capacity *= 2;
        }

        graph->edges[i++] = node;
        graph->size++;
    }
}
