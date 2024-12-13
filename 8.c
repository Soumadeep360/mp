#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#define MAX_BREAD 10

int bread_count = 0;
pthread_mutex_t lock;
pthread_cond_t cond;

void *producer(void *arg)
{
    while (1)
    {
        pthread_mutex_lock(&lock);
        while (bread_count >= MAX_BREAD)
        {
            pthread_cond_wait(&cond, &lock);
        }
        bread_count++;
        printf("Produced bread. Total: %d\n", bread_count);
        pthread_cond_broadcast(&cond);
        pthread_mutex_unlock(&lock);
        sleep(1);
    }
    return NULL;
}

void *consumer(void *arg)
{
    while (1)
    {
        pthread_mutex_lock(&lock);
        while (bread_count <= 0)
        {
            pthread_cond_wait(&cond, &lock);
        }
        bread_count--;
        printf("Consumed bread. Remaining: %d\n", bread_count);
        pthread_cond_broadcast(&cond);
        pthread_mutex_unlock(&lock);
        sleep(1);
    }
    return NULL;
}

int main()
{
    pthread_t prod_thread, cons_thread;
    pthread_mutex_init(&lock, NULL);
    pthread_cond_init(&cond, NULL);
    pthread_create(&prod_thread, NULL, producer, NULL);
    pthread_create(&cons_thread, NULL, consumer, NULL);
    pthread_join(prod_thread, NULL);
    pthread_join(cons_thread, NULL);
    pthread_mutex_destroy(&lock);
    pthread_cond_destroy(&cond);
    return 0;
}
