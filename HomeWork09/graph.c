#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>

#include "graph.h"

#ifndef INIT_SIZE
#define INIT_SIZE 10
#endif

#ifndef BUFF_SIZE
#define BUFF_SIZE 1024
#endif

#define ERR_MAL 100
#define ERR_GRA 101
#define ERR_FIL 102
#define ERR_SCA 103
#define ERR_REA 104
#define ERR_CAL 105

// - #function -----------------------------------------------------------------
void err_msg(int err_code)
{
   fprintf(stderr, "\n-----------------------------------------------------------------\n");
   fprintf(stderr, "Error:");
   switch (err_code)
   {
   case ERR_MAL:
      fprintf(stderr, "Malloc failed.");
      break;
   case ERR_GRA:
      fprintf(stderr, "Can't be non existant graph.");
      break;
   case ERR_FIL:
      fprintf(stderr, "Couldn't open a file.");
      break;
   case ERR_SCA:
      fprintf(stderr, "Failed to scan.");
      break;
   case ERR_REA:
      fprintf(stderr, "Realoc failed");
      break;
   case ERR_CAL:
      fprintf(stderr, "Calloc failed");
      break;
   }
   fprintf(stderr, "\nexiting...\n");

   exit(err_code);
}

// - function -----------------------------------------------------------------
graph_t *allocate_graph()
{
   graph_t *rah = (graph_t *)malloc(sizeof(graph_t));
   if (!rah)
   {
      err_msg(ERR_MAL);
   }
   memset(rah, 0, sizeof(graph_t));

   rah->size = 0;
   rah->capacity = INIT_SIZE;

   rah->edges = malloc((rah->capacity) * sizeof(edge_t));
   if ((!rah->edges))
   {
      err_msg(ERR_MAL);
   }
   memset(rah->edges, 0, (rah->capacity) * sizeof(edge_t));

   return rah;
}

// - #function -----------------------------------------------------------------
bool is_empty(graph_t *rah)
{
   bool ret = true;
   if (rah->size > 0)
   {
      ret = false;
   }
   return ret;
}

// - #function -----------------------------------------------------------------
bool is_full(graph_t *rah)
{
   bool ret = false;
   if ((rah->capacity) == (rah->size))
   {
      ret = true;
   }
   return ret;
}

// - function -----------------------------------------------------------------
void free_graph(graph_t **rah)
{
   if ((rah == NULL) || ((*rah) == NULL))
   {
      err_msg(ERR_GRA);
   }

   if (!is_empty(*rah))
   {
      free((*rah)->edges);
   }
   free((*rah));
   *rah = NULL;
}

// - #function -----------------------------------------------------------------
graph_t *expand_graph(graph_t *rah)
{
   rah->capacity *= 2;

   rah->edges = realloc(rah->edges, (rah->capacity) * sizeof(edge_t));
   if (!(rah->edges))
   {
      err_msg(ERR_REA);
   }
   memset(rah->edges + (rah->capacity)/2, 0, (rah->capacity)/2 * sizeof(edge_t));

   return rah;
}

// - function -----------------------------------------------------------------
void load_txt(const char *fname, graph_t *rah)
{
   if (rah == NULL)
   {
      err_msg(ERR_GRA);
   }

   FILE *o_file = fopen(fname, "r");
   if (!o_file)
   {
      err_msg(ERR_FIL);
   }

   int cur_from, cur_to, cur_cost;
   rah->size = 0;

   while (fscanf(o_file, "%d %d %d", &cur_from, &cur_to, &cur_cost) == 3)
   {
      if (is_full(rah))
      {
         expand_graph(rah);
      }

      edge_t dge = {cur_from, cur_to, cur_cost};
      rah->edges[(rah->size)++] = dge;
   }

   fclose(o_file);
}

// - function -----------------------------------------------------------------
void load_bin(const char *fname, graph_t *rah)
{
   if (rah == NULL)
   {
      err_msg(ERR_GRA);
   }

   FILE *o_file = fopen(fname, "rb");
   if (!o_file)
   {
      err_msg(ERR_FIL);
   }

   int cur_from, cur_to, cur_cost;
   rah->size = 0;

   while (fread(&cur_from, sizeof(int), 1, o_file) &&
          fread(&cur_to, sizeof(int), 1, o_file) &&
          fread(&cur_cost, sizeof(int), 1, o_file))
   {
      if (is_full(rah))
      {
         expand_graph(rah);
      }
      edge_t dge = {cur_from, cur_to, cur_cost};
      rah->edges[(rah->size)++] = dge;
   }

   fclose(o_file);
}

// - #function -----------------------------------------------------------------
void save_file(const graph_t *const rah, const char *fname, const char *modes)
{
   if (rah == NULL)
   {
      err_msg(ERR_GRA);
   }

   FILE *o_file = fopen(fname, modes);
   if (!o_file)
   {
      err_msg(ERR_FIL);
   }

   int cur_edge = -1;
   edge_t at_edge;

   while (cur_edge != (rah->size))
   {
      at_edge = (rah->edges[++cur_edge]);
      if (strcmp(modes, "w"))
      {
         fprintf(o_file, "%d %d %d\n", at_edge.from, at_edge.to, at_edge.cost);
      }

      if (strcmp(modes, "wb"))
      {
         fwrite(&at_edge.from, 4, 1, o_file);
         fwrite(&at_edge.to, 4, 1, o_file);
         fwrite(&at_edge.cost, 4, 1, o_file);
      }
   }
   fclose(o_file);
}

// - function -----------------------------------------------------------------
void save_txt(const graph_t *const rah, const char *fname)
{
   if (rah == NULL)
   {
      err_msg(ERR_GRA);
   }

   FILE *o_file = fopen(fname, "w");
   if (!o_file)
   {
      err_msg(ERR_FIL);
   }

   for (int cur_edge = 0; cur_edge < rah->size; cur_edge++)
   {
      edge_t at_edge = (rah->edges[cur_edge]);
      fprintf(o_file, "%d %d %d\n", at_edge.from, at_edge.to, at_edge.cost);
   }
   fclose(o_file);
}

// - function -----------------------------------------------------------------
void save_bin(const graph_t *const rah, const char *fname)
{
   if (rah == NULL)
   {
      err_msg(ERR_GRA);
   }

   FILE *o_file = fopen(fname, "wb");
   if (!o_file)
   {
      err_msg(ERR_FIL);
   }

   for (int cur_edge = 0; cur_edge < rah->size; cur_edge++)
   {
      edge_t at_edge = (rah->edges[cur_edge]);
      fwrite(&at_edge.from, sizeof(int), 1, o_file);
      fwrite(&at_edge.to, sizeof(int), 1, o_file);
      fwrite(&at_edge.cost, sizeof(int), 1, o_file);
   }
   fclose(o_file);
}
