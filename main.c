#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/time.h>


/* 
memset, printf, malloc, free, write,
usleep, gettimeofday, pthread_create,
pthread_detach, pthread_join, pthread_mutex_init,
pthread_mutex_destroy, pthread_mutex_lock,
pthread_mutex_unlock
 */


int main(int argc, char **argv)
{
	// if (argc != 5 || argc != 6)
	// 	exit(0);
	struct timeval startTime, endTime;
    double diff_tv_sec;
    double diff_tv_usec;

    gettimeofday(&startTime, NULL);
    usleep(1000 * 1000);
    gettimeofday(&endTime, NULL);
    diff_tv_sec = ( endTime.tv_sec - startTime.tv_sec );
    diff_tv_usec = ( endTime.tv_usec - startTime.tv_usec ) / 1000000;
    printf("%f seconds\n", diff_tv_sec); // f는 (double로) 형변환해 출력.
    printf("%f micro seconds\n", diff_tv_usec);
	return (0);
}
