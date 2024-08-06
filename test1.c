#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define N 5 // Number of philosophers

pthread_mutex_t mutex;
pthread_cond_t cond[N];
int state[N];

enum
{
	THINKING,
	HUNGRY,
	EATING
};

void test(int i)
{
	if (state[i] == HUNGRY && state[(i + N - 1) % N] != EATING && state[(i + 1) % N] != EATING)
	{
		state[i] = EATING;
		pthread_cond_signal(&cond[i]);
	}
}

void pick_up_forks(int i)
{
	pthread_mutex_lock(&mutex);
	state[i] = HUNGRY;
	test(i);
	while (state[i] != EATING)
	{
		pthread_cond_wait(&cond[i], &mutex);
	}
	pthread_mutex_unlock(&mutex);
}

void put_down_forks(int i)
{
	pthread_mutex_lock(&mutex);
	state[i] = THINKING;
	test((i + N - 1) % N);
	test((i + 1) % N);
	pthread_mutex_unlock(&mutex);
}

void *philosopher(void *num)
{
	int i = *(int *)num;
	while (1)
	{
		printf("Philosopher %d is thinking\n", i);
		sleep(1);
		pick_up_forks(i);
		printf("Philosopher %d is eating\n", i);
		sleep(1);
		put_down_forks(i);
	}
}

int main()
{
	pthread_t thread_id[N];
	int phil[N];

	pthread_mutex_init(&mutex, NULL);
	for (int i = 0; i < N; i++)
	{
		pthread_cond_init(&cond[i], NULL);
		phil[i] = i;
	}

	for (int i = 0; i < N; i++)
	{
		pthread_create(&thread_id[i], NULL, philosopher, &phil[i]);
	}

	for (int i = 0; i < N; i++)
	{
		pthread_join(thread_id[i], NULL);
	}

	pthread_mutex_destroy(&mutex);
	for (int i = 0; i < N; i++)
	{
		pthread_cond_destroy(&cond[i]);
	}

	return 0;
}
