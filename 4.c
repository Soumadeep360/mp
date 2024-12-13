#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#define SIZE 16

int array[SIZE] = {38, 27, 43, 3, 9, 82, 10, 29, 42, 2, 1, 8, 5, 6, 7, 4};

typedef struct
{
    int left;
    int right;
} thread_data;

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

void *merge_sort(void *arg)
{
    thread_data *data = (thread_data *)arg;
    int left = data->left;
    int right = data->right;

    if (left < right)
    {
        int mid = left + (right - left) / 2;

        thread_data left_data = {left, mid};
        thread_data right_data = {mid + 1, right};

        pthread_t left_thread, right_thread;
        pthread_create(&left_thread, NULL, merge_sort, &left_data);
        pthread_create(&right_thread, NULL, merge_sort, &right_data);

        pthread_join(left_thread, NULL);
        pthread_join(right_thread, NULL);

        merge(left, mid, right);
    }

    return NULL;
}

int main()
{
    pthread_t thread;
    thread_data initial_data = {0, SIZE - 1};

    pthread_create(&thread, NULL, merge_sort, &initial_data);
    pthread_join(thread, NULL);

    printf("Sorted Array:\n");
    for (int i = 0; i < SIZE; i++)
    {
        printf("%d ", array[i]);
    }
    printf("\n");

    return 0;
}
