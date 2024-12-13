#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>

#define SIZE 100
#define NUM_THREADS 4

int array[SIZE];
// int temp[SIZE];

void merge(int low, int mid, int high)
{
    int left = low;
    int right = mid + 1;
    int size = high - low + 1;
    int *temp = (int *)malloc(size * sizeof(int));
    int k = 0;

    while (left <= mid && right <= high)
    {
        if (array[left] <= array[right])
        {
            temp[k++] = array[left++];
        }
        else
        {
            temp[k++] = array[right++];
        }
    }

    while (left <= mid)
    {
        temp[k++] = array[left++];
    }

    while (right <= high)
    {
        temp[k++] = array[right++];
    }

    for (int i = 0; i < size; i++)
    {
        array[low + i] = temp[i];
    }

    free(temp);
}

void merge_sort(int left, int right)
{
    if (left >= right)
        return;
    int mid = (left + right) / 2;
    merge_sort(left, mid);
    merge_sort(mid + 1, right);
    merge(left, mid, right);
}

void *thread_sort(void *arg)
{
    int thread_part = *(int *)arg;
    int left = thread_part * (SIZE / NUM_THREADS);
    int right = (thread_part + 1) * (SIZE / NUM_THREADS) - 1;
    merge_sort(left, right);
    pthread_exit(NULL);
}

void merge_all_parts()
{
    int part_size = SIZE / NUM_THREADS;
    for (int i = 1; i < NUM_THREADS; i++)
    {
        merge(0, i * part_size - 1, (i + 1) * part_size - 1);
    }
}

int main()
{
    pthread_t threads[NUM_THREADS];
    int thread_ids[NUM_THREADS];

    for (int i = 0; i < SIZE; i++)
    {
        array[i] = rand() % 1000;
    }

    for (int i = 0; i < NUM_THREADS; i++)
    {
        thread_ids[i] = i;
        pthread_create(&threads[i], NULL, thread_sort, (void *)&thread_ids[i]);
    }

    for (int i = 0; i < NUM_THREADS; i++)
    {
        pthread_join(threads[i], NULL);
    }

    merge_all_parts();

    printf("Sorted Array:\n");
    for (int i = 0; i < SIZE; i++)
    {
        printf("%d ", array[i]);
    }
    printf("\n");

    return 0;
}
