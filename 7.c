#include <stdio.h>
#include <pthread.h>
#define NUM_THREADS 5

int account_balance = 1000;
pthread_mutex_t lock;

void *perform_transaction(void *arg)
{
    int amount = *((int *)arg);
    pthread_mutex_lock(&lock);
    if (account_balance + amount >= 0)
    {
        account_balance += amount;
        printf("Transaction successful. New balance: %d\n", account_balance);
    }
    else
    {
        printf("Transaction denied. Insufficient funds.\n");
    }
    pthread_mutex_unlock(&lock);
    return NULL;
}

int main()
{
    pthread_t threads[NUM_THREADS];
    int transactions[NUM_THREADS] = {-200, 100, -300, 150, -400};

    pthread_mutex_init(&lock, NULL);

    for (int i = 0; i < NUM_THREADS; i++)
    {
        pthread_create(&threads[i], NULL, perform_transaction, (void *)&transactions[i]);
    }

    for (int i = 0; i < NUM_THREADS; i++)
    {
        pthread_join(threads[i], NULL);
    }

    printf("Final account balance: %d\n", account_balance);
    pthread_mutex_destroy(&lock);

    return 0;
}
