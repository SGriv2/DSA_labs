#include "fibbonachi.hpp"
#include "fibbonachi_viz.hpp"

int main() {
	FibonacciHeapViz<int, int> *heap = new FibonacciHeapViz<int, int>; 
    heap->FibHeapInsert(10, 10);
    heap->FibHeapInsert(20, 20);
    heap->FibHeapInsert(30, 30);
    heap->FibHeapInsert(41, 41);
    heap->FibHeapInsert(53, 53);
    heap->FibHeapInsert(52, 52);

	FibonacciHeapViz<int, int> *heap2 = new FibonacciHeapViz<int, int>;
    heap2->FibHeapInsert(5, 5);
    heap2->FibHeapInsert(15, 15);
    heap2->FibHeapInsert(25, 25);
    heap2->FibHeapInsert(45, 45);
    heap2->FibHeapInsert(64, 64);
    heap2->FibHeapInsert(94, 94);

    heap->FibHeapUnion(heap2);

	heap->exportDOT();

    return 0;
}