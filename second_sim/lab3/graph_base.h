#include <stdio.h>
#include <stdlib.h>
#include <inttypes.h>

typedef struct graph //cоздание структуры графов
{
    uint32_t nvertices; // Число вершин
    int *m;        // Матрица n x n
    int *visited; // массив посещённых вершин
}graph;

extern graph *graph_create(uint32_t nvertices);
extern void graph_clear(graph *g);
extern void graph_free(graph *g);
extern void graph_set_edge(graph *g, int i, int j, int w);
extern int graph_get_edge(graph *g, int i, int j);
extern void graph_dfs(graph *g, int v);
extern void graph_bfs(graph *g, int v);
extern void graph_print(struct graph *g);