#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>

#define SIZE 3

int A[SIZE][SIZE] = {{1, 2, 3}, {4, 5, 6}, {7, 8, 9}};
int B[SIZE][SIZE] = {{9, 8, 7}, {6, 5, 4}, {3, 2, 1}};
int C[SIZE][SIZE];

void *add_row(void *arg)
{
    int row = *(int *)arg;
    printf("Thread ID: %lu is processing row %d\n", pthread_self(), row);
    for (int j = 0; j < SIZE; j++)
    {
        C[row][j] = A[row][j] + B[row][j];
    }
    free(arg);
    return NULL;
}

int main()
{
    pthread_t threads[SIZE];

    for (int i = 0; i < SIZE; i++)
    {
        int *row = malloc(sizeof(int));
        *row = i;
        pthread_create(&threads[i], NULL, add_row, row);
    }

    for (int i = 0; i < SIZE; i++)
    {
        pthread_join(threads[i], NULL);
    }

    for (int i = 0; i < SIZE; i++)
    {
        for (int j = 0; j < SIZE; j++)
        {
            printf("%d ", C[i][j]);
        }
        printf("\n");
    }

    return 0;
}
