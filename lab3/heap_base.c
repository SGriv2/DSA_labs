#include "heap_base.h"
#include <stdio.h>
#include <stdlib.h>

MinHeap *heap_create(int maxsize)
{
	MinHeap *h;

	h = malloc(sizeof(*h));

	if (h != NULL)
	{
		h->maxsize = maxsize;
		h->nnodes = 0;
		h->nodes = malloc(sizeof(*h->nodes) * (maxsize + 1));  /* Последний индекс - maxsize */


		if (h->nodes == NULL)
		{
		free(h);
		return NULL;
		}
	}
	
	return h;
}

void heap_free(MinHeap *h)
{
	free(h->nodes);
	free(h);
}

void heap_swap(MinHeapNode *a, MinHeapNode *b)
{
	MinHeapNode *temp = a;
	a = b;
	b = temp;
}

void min_heapify(MinHeap *heap, int index)
{
    while(1)
    {
	    int left = 2 * index;
	    int right = 2 * index + 1;
		int smallest = index;
		
	    if (left <= heap->nnodes && heap->nodes[left].key < heap->nodes[smallest].key)
	    {
		    smallest = left;
	    }
	    if (right <= heap->nnodes && heap->nodes[right].key < heap->nodes[smallest].key)
	    {
		    smallest = right;
	    }
	    if(smallest == index)
	    {
		    break;
	    }
        heap_swap(&heap->nodes[index], &heap->nodes[smallest]);
        index = smallest;
    }
}

// int HeapifyUp(MinHeap *heap, int index)
// {
// 	for (int i = heap->nnodes; i > 1 && heap->nodes[i].key < heap->nodes[i / 2].key; i = i / 2)
// 	{
// 		heap_swap(heap->nodes[i], heap->nodes[i / 2]);
// 	}
// 	return 0;
// }

int Insert_Min_Heap(MinHeap *heap, int key,int value)
{
	if (heap->nnodes >= heap->maxsize)
	{
		return -1;
	}

	heap->nnodes++;
	heap->nodes[heap->nnodes].key = key;
	heap->nodes[heap->nnodes].value = value;

	for (int i = heap->nnodes; i > 1 && heap->nodes[i].key < heap->nodes[i / 2].key; i = i / 2)
	{
		heap_swap(&heap->nodes[i], &heap->nodes[i / 2]);
	}
	return 0;
}

int heap_extract_min(MinHeap* heap)
{
	if (heap->nnodes == 0)
	{
		return 0;
	}
	MinHeapNode minnode = heap->nodes[1];
	heap->nodes[1] = heap->nodes[heap->nnodes--];
	min_heapify(heap, 1);

	return minnode.key;
}

int heap_decrease_key(MinHeap *heap,int index, int newkey)
{
    if (heap->nodes[index].key <= newkey)
	{
		return -1;
	}

	heap->nodes[index].key = newkey;
	while(index > 1 && heap->nodes[index].key < heap->nodes[index / 2].key)
	{
		heap_swap(&heap->nodes[index], &heap->nodes[index/2]);
		index = index / 2;
	}
	return index;
}

int contains(MinHeap *heap, int key)
{
    for (int i = 0; i < heap->maxsize; i++)
    {
        if (heap->nodes[i].key == key)
        {
            return 1;
        }
    }
    return 0;
}


void heapify_down(MinHeap *heap, int index)
{
    int left = 2 * index + 1;
    int right = 2 * index + 2;
    int smallest = index; //Инициализирует индекс самого маленького элемента smallest как index.

    if (left < heap->maxsize && heap->nodes[left].value < heap->nodes[smallest].value)//Проверяет, существует ли левый дочерний узел и имеет ли он меньший приоритет, чем у элемента по индексу index. Если это так, обновляет smallest до left.
    {
        smallest = left;
    }

    if (right < heap->maxsize && heap->nodes[right].value < heap->nodes[smallest].value) //Проверяет, существует ли правый дочерний узел и имеет ли он меньший приоритет, чем у элемента по индексу smallest. Если это так, обновляет smallest до right.
    {
        smallest = right;
    }

    if (smallest != index)
    {
        heap_swap(&heap->nodes[index], &heap->nodes[smallest]);
        heapify_down(heap, smallest);
    }
   // Проверяет, отличается ли smallest от index. Если это так, значит, один из дочерних узлов имеет меньший приоритет, чем родительский узел. В этом случае:
   // Меняет местами родительский узел и самый маленький дочерний узел, используя функцию swap.
   // Рекурсивно вызывает heapify_down для самого маленького дочернего узла, чтобы продолжить просеивание.
}