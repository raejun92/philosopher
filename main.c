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

void p_function(void *data)
{
	pthread_t tid;

	tid = pthread_self();

	char *thread_name = (char *)data;
	int i = 0;

	while (i < 3) {
		printf("thread name: %s, tid: %x\n", thread_name, (unsigned int)tid);
		i++;
		usleep(1000 * 1000);
	}
}

int main(int argc, char **argv)
{
	// if (argc != 5 || argc != 6)
	// 	exit(0);
	pthread_t pthread;
	int thr_id;
	int status;
	char p1[] = "thread_created";
	char p2[] = "thread_main";

	thr_id = pthread_create(&pthread, NULL, p_function, (void *)p1);
	if (thr_id < 0) {
		perror("thread0 create error");
		exit(EXIT_FAILURE);
	}

	p_function((void *)p2);

	printf("created thread id: %x\n", pthread);
	printf("end\n");
	return (0);
}
