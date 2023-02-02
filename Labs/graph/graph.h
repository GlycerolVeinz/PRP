#ifndef __GRAPH_H__
#define __GRAPH_H__

typedef struct {
   int from;
   int to;
   int cost;
} edge_t;
 
typedef struct {
  edge_t **edges;
  int size;
  int capacity;
} graph_t;

#endif // __GRAPH_H__
