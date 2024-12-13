#include <stdio.h>
#include <pthread.h>

#define SIZE 100
#define NUM_THREADS 4

int data[SIZE];
int found_index = -1;
pthread_mutex_t lock;

void* search(void* arg) {
    int start = *(int*)arg;
    int end = start + (SIZE / NUM_THREADS);

    for (int i = start; i < end; i++) {
        if (data[i] == 50) {
            pthread_mutex_lock(&lock);
            found_index = i;
            pthread_mutex_unlock(&lock);
            return NULL;
        }
    }
    return NULL;
}

int main() {
    pthread_t threads[NUM_THREADS];
    int thread_ids[NUM_THREADS];

    for (int i = 0; i < SIZE; i++) {
        data[i] = i + 1;
    }

    pthread_mutex_init(&lock, NULL);

    for (int i = 0; i < NUM_THREADS; i++) {
        thread_ids[i] = i * (SIZE / NUM_THREADS);
        pthread_create(&threads[i], NULL, search, (void*)&thread_ids[i]);
    }

    for (int i = 0; i < NUM_THREADS; i++) {
        pthread_join(threads[i], NULL);
    }

    if (found_index != -1) {
        printf("Number 50 found at index: %d\n", found_index);
    } else {
        printf("Number 50 not found.\n");
    }

    pthread_mutex_destroy(&lock);
    return 0;
}
