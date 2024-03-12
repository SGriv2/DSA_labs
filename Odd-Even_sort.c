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

void OddEvensort(uint32_t *arr, unsigned int n)
{
    int flag = 0;
    int i = 0;

    while (!flag)
    {
        flag = 1;

        i = 1;
        while (i < n)
        {
            if (arr[i] > arr[i + 1])
            {
                swap(arr, i, i + 1);
                flag = 0;
            }
            i = i + 2;
        }

        i = 0;
        while (i < n - 1)
        {
            if (arr[i] > arr[i + 1])
            {
                swap(arr, i, i + 1);
                flag = 0;
            }
            i = i + 2;
        }
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
    unsigned int n = 950000;
    uint32_t *array;
    array = (uint32_t *)malloc(n * sizeof(int));
    random_el(array, n);

    OddEvensort(array, n);

    print_array(array, n);
    printf("Время сортировки %d элементов: %.2f\n", n, wtime() - start_time);

    return 0;
}
