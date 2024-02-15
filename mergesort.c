#include <stdio.h>
#include <sys/time.h>
#include <stdlib.h>

#define TYPE long int

void merge(TYPE arr[], int left, int right, int mid);
void print_array(TYPE arr[], long int length);

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

void merge_sort(TYPE arr[], int left, int right)
{
    if (left < right)
    {
        int mid = left + (right - left) / 2;

        merge_sort(arr, left, mid);
        merge_sort(arr, mid + 1, right);

        merge(arr, left, right, mid);
    }
}

void merge(TYPE arr[], int left, int right, int mid)
{
    int size_left = mid - left + 1;
    int size_right = right - mid;
    int arrL[size_left];
    int arrR[size_right];
    for (TYPE i = 0; i < size_left; i++)
    {
        arrL[i] = arr[left + i];
    }

    for (TYPE j = 0; j < size_right; j++)
    {
        arrR[j] = arr[mid + 1 + j];
    }
    TYPE k = left;
    TYPE l = 0;
    TYPE r = 0;
    while (l < size_left && r < size_right)
    {
        if (arrL[l] <= arrR[r])
        {
            arr[k] = arrL[l];
            l++;
        }
        else
        {
            arr[k] = arrR[r];
            r++;
        }
        k++;
    }
    while (l < size_left)
    {
        arr[k] = arrL[l];
        l++;
        k++;
    }
    while (r < size_right)
    {
        arr[k] = arrR[r];
        r++;
        k++;
    }
}

void print_array(TYPE arr[], TYPE length)
{
    for (int i = 0; i < length; i++)
    {
        printf("%ld ", arr[i]);
    }
    printf("\n");
}

int main()
{
    TYPE n = 250000;
    TYPE array[n];
    double t = wtime();
    for (TYPE i = 0; i < n; i++)
    {
        array[i] = getrand(1, 100000);
    }
    int size = sizeof(array) / sizeof(array[0]);

    merge_sort(array, 0, size - 1);

    t = wtime() - t;
    print_array(array, n);
    printf("Elapsed time: %.6f sec.\n", t);

    return 0;
}
