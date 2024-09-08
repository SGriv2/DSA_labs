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

int main()
{
    for (int i = 0; i <= 20; i++)
    {
        unsigned int n = i * 50000;
        uint32_t *arr;
        arr = (uint32_t *)malloc(n * sizeof(int));
        random_el(arr, n);

        double start_time = wtime();

        Insertion_sort(arr, n);

        printf("Время сортировки %d элементов: %f\n", n, wtime() - start_time);
    }
    return 0;
}
