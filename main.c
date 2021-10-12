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
 */

void *t_function(void *param)
{
	printf("쓰레드 함수 실행\n");
	for (int i = 0; i <= 5; i++)
	{
		usleep(1000 * 1000);
		printf("쓰레드 함수 실행 중...(%d/5)\n", i);
	}
	printf("쓰레드 함수 종료\n");
	return (void *)2147483647;
}

int main(int argc, char **argv)
{
	// if (argc != 5 || argc != 6)
	// 	exit(0);
	pthread_t p_thread;
	int thr_id;
	int result;

	thr_id = pthread_create(&p_thread, NULL, t_function, NULL);
	if (thr_id < 0)
	{
		perror("thread create error:;");
		exit(0);
	}
	pthread_join(p_thread, (void *)&result);
	printf("thread join 실행됨:%d\n", result);
	printf("main() 종료\n");
	return (0);
}
