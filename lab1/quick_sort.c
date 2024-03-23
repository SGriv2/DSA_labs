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

void Quick_sort(uint32_t *arr, int low, int high)
{
    int i = low;
    int j = high;
    int pivot = arr[(low + high) / 2];

    do
    {
        while (arr[i] < pivot)
        {
            i++;
        }
        while (arr[j] > pivot)
        {
            j--;
        }
        if (i <= j)
        {
            if (arr[i] > arr[j])
            {
                int tmp = arr[i];
                arr[i] = arr[j];
                arr[j] = tmp;
            }
            i++;
            if (j > 0)
            {
                j--;
            }
        }
    } while (i <= j);

    if (i < high)
    {
        Quick_sort(arr, i, high);
    }
    if (j > low)
    {
        Quick_sort(arr, low, j);
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
    for (int i = 0; i <= 20; i++)
  {
    unsigned int n = i * 50000;
    uint32_t *arr;
    arr = (uint32_t *)malloc(n * sizeof(int));
    random_el(arr, n);

    double start_time = wtime();

    Quick_sort(arr, 0, n);

    printf("Время сортировки %d элементов: %f\n", n, wtime() - start_time);
  }
}
