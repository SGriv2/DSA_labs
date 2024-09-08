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

void swap(uint32_t *arr, int i, int j)
{
    int temp = arr[i];
    arr[i] = arr[j];
    arr[j] = temp;
}

void bubbleSort(uint32_t *arr, int n)
{
    int i, j;
    for (i = 0; i < n - 1; i++)
        for (j = 0; j < n - i - 1; j++)
            if (arr[j] > arr[j + 1])
                swap(arr, j, j + 1);
}

int main()
{
   for (int i = 0; i <= 20; i++)
  {
    unsigned int n = i * 50000;
    uint32_t *arr;
    arr = (uint32_t *)malloc(n * sizeof(int));
    random_el(arr, n);

    double start_time = wtime();

    bubbleSort(arr, n);

    printf("Время сортировки %d элементов: %f\n", n, wtime() - start_time);
  }
}
