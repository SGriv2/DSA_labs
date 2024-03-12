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

void Insertion_sort(uint32_t *arr, unsigned int n)
{
    int temp, k;
    for (int i = 1; i < n; i++)
    {
        temp = arr[i];
        k = i - 1;
        while (k >= 0 && arr[k] > temp)
        {
            arr[k + 1] = arr[k];
            --k;
        }
        arr[k + 1] = temp;
    }
}

void printArray(uint32_t arr[], int size)
{
    for (int i = 0; i < size; i++)
    {
        printf("%d ", arr[i]);
    }
    printf("\n");
}

int main()
{
    double start_time = wtime();
    unsigned int n = 1000000;
    uint32_t *arr;
    arr = (uint32_t *)malloc(n * sizeof(int));
    random_el(arr, n);
    Insertion_sort(arr, n);
    printArray(arr, n);
    printf("\n");
    printf("Время сортировки %d элементов: %f\n", n, wtime() - start_time);
    return 0;
}
