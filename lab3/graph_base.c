#include "graph_base.h"
#include <stdio.h>

graph *graph_create(uint32_t nvertices)
{
    graph *g;

    g = malloc(sizeof(*g));
    g->nvertices = nvertices;
    g->m = malloc(sizeof(int) * nvertices * nvertices);
    g->visited = malloc(sizeof(int) * nvertices);

    graph_clear(g);
    return g;
}

void graph_clear(graph *g)
{
    int i, j;
    for(i = 0; i < g->nvertices; i++)
    {
        g->visited[i] = 0;
        for(j = 0; j < g->nvertices; j++)
        {
            g->m[i * g->nvertices + j] = 0;
        }
    }
}

void graph_free(graph *g)
{
    free(g->m);
    free(g->visited);
    free(g);
}

void graph_set_edge(graph *g, int i, int j, int w)
{
    g->m[(i - 1) * g->nvertices + j - 1] = w;
    g->m[(j - 1) * g->nvertices + i - 1] = w;
}

int graph_get_edge(graph *g, int i, int j)
{
    return g->m[(i-1) * g->nvertices + j - 1];
}


