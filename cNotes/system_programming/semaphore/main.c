#include<stdio.h>
#include <unistd.h>
#include <pthread.h>
#include<semaphore.h>

sem_t my_sem1;
sem_t my_sem2;
sem_t my_sem3;

void *thread1(void *arg)
{
	while(1)
	{
		sem_wait(&my_sem1);
		sem_wait(&my_sem3);
		printf("thread1\n");
		sem_post(&my_sem3);
		sem_post(&my_sem1);
		//usleep(1000000);
	}
}
void *thread2(void *arg)
{
	while(1)
	{
		sem_wait(&my_sem2);
		sem_wait(&my_sem1);
		printf("thread2\n");
		sem_post(&my_sem1);
		sem_post(&my_sem2);
		//usleep(1000000);
	}
}
void *thread3(void *arg)
{
	while(1)
	{
		sem_wait(&my_sem3);
		sem_wait(&my_sem2);
		printf("thread3\n");
		sem_post(&my_sem2);
		sem_post(&my_sem3);
		//usleep(1000000);
	}
}

int main()
{
	pthread_t t1, t2, t3;
	sem_init(&my_sem1, 0, 1); 
	sem_init(&my_sem2, 0, 1); 
	sem_init(&my_sem3, 0, 1); 
	int ret = pthread_create(&t1, NULL, thread1, NULL);
	ret = pthread_create(&t2, NULL, thread2, NULL);
	ret = pthread_create(&t3, NULL, thread3, NULL);

	pthread_join(t1, NULL);
	pthread_join(t2, NULL);
	pthread_join(t3, NULL);
	return 0;
}
