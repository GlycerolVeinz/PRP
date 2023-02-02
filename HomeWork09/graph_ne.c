#include <stdio.h>
#include <stdlib.h>
#include "graph.h"

#define GRAPH_INITIAL_CAPACITY 10
#define GRAPH_CAPACITY_MULTIPLIER 2

graph_t *allocate_graph()
{
    graph_t *graph = malloc(sizeof(graph_t));
    graph->edges = malloc(GRAPH_INITIAL_CAPACITY * sizeof(edge_t));
    graph->size = 0;
    graph->capacity = GRAPH_INITIAL_CAPACITY;
    return graph;
}

void free_graph(graph_t **graph)
{
    free((*graph)->edges);
    free(*graph);
    *graph = NULL;
}

void load_txt(const char *fname, graph_t *graph)
{
    FILE *fp = fopen(fname, "r");
    if (fp == NULL)
    {
        fprintf(stderr, "Error opening file %s\n", fname);
        return;
    }
    int from, to, cost;
    while (fscanf(fp, "%d,%d,%d", &from, &to, &cost) == 3)
    {
        if (graph->size == graph->capacity)
        {
            graph->capacity *= GRAPH_CAPACITY_MULTIPLIER;
            graph->edges = realloc(graph->edges, graph->capacity * sizeof(edge_t));
        }
        edge_t edge = {from, to, cost};
        graph->edges[graph->size++] = edge;
    }
    fclose(fp);
}

void load_bin(const char *fname, graph_t *graph)
{
    FILE *fp = fopen(fname, "rb");
    if (fp == NULL)
    {
        fprintf(stderr, "Error opening file %s\n", fname);
        return;
    }
    while (fread(&graph->edges[graph->size], sizeof(edge_t), 1, fp))
    {
        if (++graph->size == graph->capacity)
        {
            graph->capacity *= GRAPH_CAPACITY_MULTIPLIER;
            graph->edges = realloc(graph->edges, graph->capacity * sizeof(edge_t));
        }
    }
    fclose(fp);
}

void save_txt(const graph_t *const graph, const char *fname)
{
    FILE *fp = fopen(fname, "w");
    if (fp == NULL)
    {
        fprintf(stderr, "Error opening file %s\n", fname);
        return;
    }
    for (int i = 0; i < graph->size; i++)
    {
        fprintf(fp, "%d,%d,%d\n", graph->edges[i].from, graph->edges[i].to, graph->edges[i].cost);
    }
    fclose(fp);
}

void save_bin(const graph_t *const graph, const char *fname)
{
    FILE
        *fp = fopen(fname, "wb");
    if (fp == NULL)
    {
        fprintf(stderr, "Error opening file %s\n", fname);
        return;
    }
    for (int i = 0; i < graph->size; i++)
    {
        fwrite(&graph->edges[i], sizeof(edge_t), 1, fp);
    }
    fclose(fp);
}
