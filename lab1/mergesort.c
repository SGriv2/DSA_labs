#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <time.h>
#include <stdint.h>

void merge(uint32_t arr[], int left, int right, int mid);
void print_array(uint32_t arr[], int length);

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

void merge_sort(uint32_t *arr, int l, int r)
{
    if (l < r)
    {

        int m = l + (r - l) / 2;

        merge_sort(arr, l, m);
        merge_sort(arr, m + 1, r);

        merge(arr, l, m, r);
    }
}

void merge(uint32_t *arr, int l, int m, int r)
{
    int i, j, k;
    unsigned int n1 = m - l + 1;
    unsigned int n2 = r - m;
    uint32_t *L = (uint32_t *)malloc(n1 * sizeof(int));
    uint32_t *R = (uint32_t *)malloc(n2 * sizeof(int));

    for (i = 0; i < n1; i++)
        L[i] = arr[l + i];
    for (j = 0; j < n2; j++)
        R[j] = arr[m + 1 + j];

    i = 0;
    j = 0;
    k = l;
    while (i < n1 && j < n2)
    {
        if (L[i] <= R[j])
        {
            arr[k] = L[i];
            i++;
        }
        else
        {
            arr[k] = R[j];
            j++;
        }
        k++;
    }

    while (i < n1)
    {
        arr[k] = L[i];
        i++;
        k++;
    }
    while (j < n2)
    {
        arr[k] = R[j];
        j++;
        k++;
    }
}

int main()
{
    for (int i = 0; i <= 20; i++)
    {
        unsigned int n = i * 50000;
        uint32_t *array;
        array = (uint32_t *)malloc(n * sizeof(int));
        random_el(array, n);

        double start_time = wtime();

        merge_sort(array, 0, n - 1);

        printf("Время сортировки %d элементов: %f\n", n, wtime() - start_time);

        free(array);
    }
    return 0;
}
