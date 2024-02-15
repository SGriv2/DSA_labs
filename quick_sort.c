#include <stdio.h>
#include <sys/time.h>
#include <stdlib.h>

int getrand(int min, int max)
{
    return (double)rand() / (RAND_MAX + 1.0) * (max - min) + min;
}

double wtime()
{
    struct timeval t;
    gettimeofday(&t, NULL);
    return (double)t.tv_sec + (double)t.tv_usec * 1E-6;
}

void quicksort(int arr[], int low, int high)
{
    if (low < high)
    {
        int pivot = arr[(low + high) / 2];
        int i = low;
        int j = high;

        while (i <= j)
        {
            while (arr[i] < pivot)
                i++;
            while (arr[j] > pivot)
                j--;

            if (i <= j)
            {
                swap(&arr[i], &arr[j]);
                i++;
                j--;
            }
        }

        if (low < j)
            quicksort(arr, low, j);
        if (i < high)
            quicksort(arr, i, high);
    }
}

void swap(int *a, int *b)
{
    int tmp = *a;
    *a = *b;
    *b = tmp;
}

void printArray(int arr[], int size)
{
    for (int i = 0; i < size; i++)
    {
        printf("%d ", arr[i]);
    }
    printf("\n");
}

int main()
{
    int n = 50000;
    int array[n];
    double t = wtime();
    for (int i = 0; i < n; i++)
    {
        array[i] = getrand(1, 1000000);
    }

    t = wtime() - t;
    printf("Elapsed time: %.16f sec.\n", t);

    return 0;
}
