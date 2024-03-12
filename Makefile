run_merge: mergesort.c
	gcc -Wall -Werror -o app mergesort.c -lm -g

run_quick: quick_sort.c
	gcc -Wall -Werror -o app quick_sort.c -lm

run_counting: counting_sort.c
	gcc -Wall -Werror -o app counting_sort.c -lm

run_insert: insertsort.c
	gcc -Wall -Werror -o app insertsort.c -lm

run_buble: buble_sort.c
	gcc -Wall -Werror -o app buble_sort.c -lm

run_Heap: Heap_sort.c
	gcc -Wall -Werror -o app Heap_sort.c -lm

run_Odd: Odd-Even_sort.c
	gcc -Wall -Werror -o app Odd-Even_sort.c -lm

run_Radix: Radix_sort.c
	gcc -Wall -Werror -o app Radix_sort.c -lm

run_Selection: Selection_sort.c
	gcc -Wall -Werror -o app Selection_sort.c -lm
	
clean: app
	rm app