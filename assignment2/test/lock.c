#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

#define NUM_THREADS 3

pthread_mutex_t lock_x;

void *functionThread(void *arg){

	printf("Hello from thread function. Thread is: %d\n", pthread_self());

	pthread_mutex_lock(&lock_x);

	printf("Do something here\n");

	pthread_mutex_unlock(&lock_x);

	pthread_exit(NULL);
}

int main(int argc, char **argv){
	pthread_t thr[NUM_THREADS];
	int rc;

	pthread_mutex_init(&lock_x, NULL);

	if((rc = pthread_create(&thr[0], NULL, functionThread, NULL))){
		printf("Error creating thread\n");
	}

	if((rc = pthread_create(&thr[1], NULL, functionThread, NULL))){
		printf("Error creating thread\n");
	}

	if((rc = pthread_create(&thr[2], NULL, functionThread, NULL))){
		printf("Error creating thread\n");
	}

	pthread_join(thr[0], NULL);
	pthread_join(thr[1], NULL);
	pthread_join(thr[2], NULL);

	return EXIT_SUCCESS;
}