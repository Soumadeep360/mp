#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>

#define SIZE 16

int a[SIZE] = {38, 27, 43, 3, 9, 82, 10, 29, 42, 2, 1, 8, 5, 6, 7, 4};

void merge(int low, int mid, int high)
{
    int *temp = (int *)malloc((high - low + 1) * sizeof(int));
    int left = low;
    int right = mid + 1;
    int k = 0;
    while (left <= mid && right <= high)
    {
        if (a[left] < a[right])
        {
            temp[k++] = a[left++];
        }
        else
        {
            temp[k++] = a[right++];
        }
    }
    while (left <= mid)
        temp[k++] = a[left++];
    while (right <= high)
        temp[k++] = a[right++];
    for (int i = 0; i < high - low + 1; i++)
    {
        a[i + low] = temp[i];
    }
    free(temp);
}

void *merge_sort(void *arg)
{
    int *ind = (int *)arg;
    int low = ind[0];
    int high = ind[1];
    if (low < high)
    {
        int mid = low + (high - low) / 2;
        int left_ind[2] = {low, mid};
        int right_ind[2] = {mid + 1, high};
        pthread_t left_thread, right_thread;
        pthread_create(&left_thread, NULL, merge_sort, left_ind);
        pthread_create(&right_thread, NULL, merge_sort, right_ind);
        pthread_join(left_thread, NULL);
        pthread_join(right_thread, NULL);

        merge(low, mid, high);
    }
}

int main()
{
    pthread_t thread;
    int ind[2] = {0, SIZE - 1};
    pthread_create(&thread, NULL, merge_sort, ind);
    pthread_join(thread, NULL);
    for (int i = 0; i < SIZE; i++)
    {
        printf("%d ", a[i]);
    }
    printf("\n");
}
