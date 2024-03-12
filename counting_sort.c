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

void Counting_sort(uint32_t *arr, int n)
{
  int output[n];

  int max = arr[0];
  for (int i = 1; i < n; i++)
  {
    if (arr[i] > max)
      max = arr[i];
  }
  int count[max];

  for (int i = 0; i <= max; ++i)
  {
    count[i] = 0;
  }
  for (int i = 0; i < n; i++)
  {
    count[arr[i]]++;
  }
  for (int i = 1; i <= max; i++)
  {
    count[i] += count[i - 1];
  }
  for (int i = n - 1; i >= 0; i--)
  {
    output[count[arr[i]] - 1] = arr[i];
    count[arr[i]]--;
  }
  for (int i = 0; i < n; i++)
  {
    arr[i] = output[i];
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
  Counting_sort(arr, n);
  printArray(arr, n);
  printf("\n");
  printf("Время сортировки %d элементов: %f\n", n, wtime() - start_time);
  return 0;
}
