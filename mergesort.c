#include <stdio.h>
#include <sys/time.h>
#include <stdlib.h>

void merge(int arr[], int left, int right, int mid);
void print_array(int arr[], int length);

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

void merge_sort(int arr[], int left, int right)
{
    if (left < right)
    {
        int mid = left + (right - left) / 2;

        merge_sort(arr, left, mid);
        merge_sort(arr, mid + 1, right);

        merge(arr, left, right, mid);
    }
}

void merge(int arr[], int left, int right, int mid)
{
    int size_left = mid - left + 1;
    int size_right = right - mid;
    int arrL[size_left];
    int arrR[size_right];
    for (int i = 0; i < size_left; i++)
    {
        arrL[i] = arr[left + i];
    }

    for (int j = 0; j < size_right; j++)
    {
        arrR[j] = arr[mid + 1 + j];
    }
    int k = left;
    int l = 0;
    int r = 0;
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

void print_array(int arr[], int length)
{
    for (int i = 0; i < length; i++)
    {
        printf("%d ", arr[i]);
    }
    printf("\n");
}

int main()
{
    int n = 950000;
    int array[n];
    for (int i = 0; i < n; i++)
    {
        array[i] = getrand(1, 100000);
    }
    int size = sizeof(array) / sizeof(array[0]);

    merge_sort(array, 0, size - 1);

    double t = wtime();

    t = wtime() - t;
    printf("Elapsed time: %.16f sec.\n", t);

    return 0;
}
