#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/time.h>
#include <pthread.h>


/* 
memset, printf, malloc, free, write,
usleep, gettimeofday, pthread_create,
pthread_detach, pthread_join, pthread_mutex_init,
pthread_mutex_destroy, pthread_mutex_lock,
pthread_mutex_unlock

식사를 마치면 포크를 내려놓고 잠을 잔다
잠을 다 자면 생각한다
생각 후 식사한다
 */
pthread_mutex_t mutex;
int cnt = 0;

void *count(void *arg)
{
	int i;
	char *name = (char *)arg;

	pthread_mutex_lock(&mutex);

	cnt = 0;
	for (i = 0; i < 10; i++)
	{
		printf("%s cnt: %d\n", name, cnt);
		cnt++;
		usleep(1);
	}
	
	pthread_mutex_unlock(&mutex);
}

int main(int argc, char **argv)
{
	// if (argc != 5 || argc != 6)
	// 	exit(0);
	pthread_t thread1, thread2;

	pthread_mutex_init(&mutex, NULL);
	
	pthread_create(&thread1, NULL, count, (void *)"thread1");
	pthread_create(&thread2, NULL, count, (void *)"thread2");

	pthread_join(thread1, NULL);
	pthread_join(thread2, NULL);

	pthread_mutex_destroy(&mutex);
	return (0);
}