#include <stdio.h>

typedef struct MinHeapNode
{
	int key;      /* Приоритет (ключ) */
	int value;  /* Значение */
}MinHeapNode;

typedef struct MinHeap
{
	int maxsize;     /* Максимальный размер кучи */
	int nnodes;      /* Число элементов */
	MinHeapNode *nodes; /* Массив элементов. Для удобства реализации элементы нумеруются с 1 */
}MinHeap;

extern int HeapifyUp(MinHeap *heap, int index);
extern MinHeap *heap_create(int maxsize);
extern void heap_free(MinHeap *h);
extern void heap_swap(MinHeapNode *a, MinHeapNode *b);
extern void min_heapify(MinHeap *heap, int index);
extern int Insert_Min_Heap(MinHeap *heap, int key,int value);
extern void Heapifydown(MinHeap *heap, int index);
extern int heap_extract_min(MinHeap* heap);
extern int heap_decrease_key(MinHeap *heap, int index, int newkey);
extern int contains(MinHeap *heap, int key);
extern void heapify_down(MinHeap *heap, int index);

