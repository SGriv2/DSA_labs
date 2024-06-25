#include <stdio.h>
#include <stdlib.h>
#include "heap_base.h"
#include "graph_base.h"
#include <sys/time.h>
#include <time.h>
#define INFINITY 99999

double wtime()
{
    struct timeval t;
    gettimeofday(&t, NULL);
    return (double)t.tv_sec + (double)t.tv_usec * 1E-6;
}

int random_el(int min, int max)
{
    return (double)rand() / (RAND_MAX + 1.0) * (max - min) + min;
}

int *SearchShortestPath(int src, int dst, int *prev, int *dist)
{
    int i = dst - 1;
    int pathlen = 1;
    while (prev[i] != src)
    {
        pathlen = pathlen + 1;
        i = prev[i] - 1;
    }
    int j = 0;
    i = dst - 1;
    int *path = malloc(100000 * sizeof(int));
    while (i != src - 1)
    {
        path[pathlen - j] = i + 1;

        i = prev[i] - 1;
        j = j + 1;
    }

    path[pathlen - j] = i + 1;

    i = prev[i] - 1;
    j = j + 1;

    // по индексам от 0 до 3

    for (int i = 0; i <= pathlen; i++)
    {
        printf("%d ", path[i]);
    }
    printf("Длина пути = %d", dist[dst - 1]);
    printf("\n");

    return path;
}
 

void dijkstra(struct graph *graph, int src, int *prev, int *dist)
{

    MinHeap *heap = heap_create(100000);
    for (int i = 1; i < graph->nvertices + 1; i++)
    {
        dist[i] = INFINITY;
        prev[i] = -1;
    }
    // путь до самой вершины равен 0, prev -1
    dist[src] = 0;
    prev[src] = -1;

    Insert_Min_Heap(heap, src, dist[src]);

    // Основной цикл алгоритма Дейкстры
    while (heap != NULL)
    {
        int u = heap_extract_min(heap);

        // Цикл для каждого соседа вершины u
        for (int v = 0; v < graph->nvertices; v++)
        {
            if (graph->m[u * graph->nvertices + v] > 0) // проход по смежным вершинам
            {
                int alt = dist[u] + graph->m[u * graph->nvertices + v]; // Новая длина пути
                // printf("для u =%d, смежная v = %d\n", u + 1, v + 1);
                //  Если новая длина пути короче текущей, обновляем информацию о вершине v
                if (alt < dist[v])
                {
                    dist[v] = alt;
                    prev[v] = u + 1;

                    // Если вершина v уже есть в куче, уменьшаем её приоритет
                    if (contains(heap, v))
                    {
                        heap_decrease_key(heap, v, alt);
                    }
                    else
                    { // Иначе добавляем её в кучу
                        Insert_Min_Heap(heap, v, alt);
                    }
                }
            }
        }
    }
    /*
    printf("Vertex \t Distance \t Previous\n");
    for (int i = 0; i < graph->nvertices; i++)
    {
        printf("%d \t %d \t\t %d\n", i + 1, dist[i], prev[i]);
    }*/
}

int main()
{
    graph *g20;
    graph *g100;

    // создание создания графа-решётки размером 100x100
    //int size = 5;
    g100 = graph_create(5 * 5);
    for (int i = 1; i <= 5; i++)
    {
        for (int j = 1; j <= 5; j++)
        {
            int v = (i - 1) * 5 + j; // Получаем номер вершины по её координатам
            if (i > 1)
                graph_set_edge(g100, v, v - 5, random_el(1, 50)); // Связываем с вершиной выше
            if (j > 1)
                graph_set_edge(g100, v, v - 1, random_el(1, 50)); // Связываем с вершиной слева
        }
    }

    g20 = graph_create(20);
    // for (int i = 1; i < 21; i++)
    // {
    //     graph_set_edge(g20, i, i+1, random_el(1, 20));
    // }

    graph_set_edge(g20, 1, 2, 10);
    graph_set_edge(g20, 4, 1, 20);
    graph_set_edge(g20, 3, 2, 5);
    graph_set_edge(g20, 1, 5, 2);
    graph_set_edge(g20, 2, 5, 6);
    graph_set_edge(g20, 3, 5, 9);
    graph_set_edge(g20, 3, 4, 12);
    graph_set_edge(g20, 4, 5, 15);
    graph_set_edge(g20, 3, 8, 19);
    graph_set_edge(g20, 6, 7, 17);
    graph_set_edge(g20, 7, 8, 15);
    graph_set_edge(g20, 8, 9, 14);
    graph_set_edge(g20, 8, 10, 12);
    graph_set_edge(g20, 10, 11, 25);
    graph_set_edge(g20, 9, 12, 24);
    graph_set_edge(g20, 13, 11, 29);
    graph_set_edge(g20, 13, 12, 27);
    graph_set_edge(g20, 13, 14, 26);
    graph_set_edge(g20, 14, 15, 31);
    graph_set_edge(g20, 15, 17, 34);
    graph_set_edge(g20, 15, 16, 32);
    graph_set_edge(g20, 17, 19, 41);
    graph_set_edge(g20, 16, 18, 9);
    graph_set_edge(g20, 19, 20, 18);

    // график 5 вершин из презентации
   /* g = graph_create(50);
    graph_set_edge(g, 1, 5, 100);
    graph_set_edge(g, 1, 2, 10);
    graph_set_edge(g, 1, 4, 30);
    graph_set_edge(g, 2, 3, 50);
    graph_set_edge(g, 3, 5, 10);
    graph_set_edge(g, 3, 4, 20);
    graph_set_edge(g, 4, 5, 60);*/

    // алгоритм дейкстры для связного графа из 20 вершин
    int dist1[g20->nvertices];
    int *prev1 = malloc(sizeof(int) * g20->nvertices);

    double timer1 = wtime();
    dijkstra(g20, 0, prev1, dist1);
    timer1 = wtime() - timer1;
    printf("Время работы алгоритма Дейкстры:  %f\n", timer1);

    for (int i = 2; i < 3; i++)
    {
        printf("Кратчайший путь от 1 вершины до %d: ", i);
        SearchShortestPath(1, i, prev1, dist1);
    }

    // алгоритм дейкстры для графа-решётки размером 100x100

    int dist2[g100->nvertices];
    int *prev2 = malloc(sizeof(int) * g100->nvertices);
    double timer2 = wtime();
    dijkstra(g100, 0, prev2, dist2);
    timer2 = wtime() - timer2;
    printf("Время работы алгоритма Дейкстры:  %f\n", timer2);


    for (int i = 2; i < 4; i++)
    {
        printf("Кратчайший путь от 1 вершины до %d: ", i);
        SearchShortestPath(1, i, prev2, dist2);
    }

    // for(int i = 0; i < g100->nvertices;i++)
    // {
    //     for(int j = 0; i < g100->nvertices;j++)
    //     {
    //         printf("%d ", g100->m[(i) * g100->nvertices + j]);
    //     }
    // }

    graph_free(g20);
    graph_free(g100);
}