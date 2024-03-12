#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <time.h>
#include <stdint.h>

double wtime()
{
    struct timeval t;
    gettimeofday(&t, NULL);
    return (double)t.tv_sec + (double)t.tv_usec * 1E-6;
}

void random_el(uint32_t *arr, unsigned int n)
{
    srand(time(NULL));
    for (int i = 0; i < n; i++)
    {
        arr[i] = rand() % 100000;
    }
}

void heapify(uint32_t *arr, int n, int i)
{
    int temp, maximum, left_index, right_index;

    maximum = i;

    right_index = 2 * i + 2;

    left_index = 2 * i + 1;

    if (left_index < n && arr[left_index] > arr[maximum])
        maximum = left_index;

    if (right_index < n && arr[right_index] > arr[maximum])
        maximum = right_index;

    if (maximum != i)
    {
        temp = arr[i];
        arr[i] = arr[maximum];
        arr[maximum] = temp;
        heapify(arr, n, maximum);
    }
}

void heapsort(uint32_t *arr, int n)
{
    int i, temp;

    for (i = n / 2 - 1; i >= 0; i--)
    {
        heapify(arr, n, i);
    }

    for (i = n - 1; i > 0; i--)
    {
        temp = arr[0];
        arr[0] = arr[i];
        arr[i] = temp;
        heapify(arr, i, 0);
    }
}

void print_array(uint32_t arr[], int length)
{
    for (int i = 0; i < length; i++)
    {
        printf("%d ", arr[i]);
    }
    printf("\n");
}

int main()
{
    double start_time = wtime();
    unsigned int n = 100000;
    uint32_t *array;
    array = (uint32_t *)malloc(n * sizeof(int));
    random_el(array, n);

    heapsort(array, n);

    print_array(array, n);
    printf("Время сортировки %d элементов: %.2f\n", n, wtime() - start_time);

    return 0;
}
