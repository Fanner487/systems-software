#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

void *print_message_function(void *ptr);

void main(){

	pthread_t thread1, thread2;
	const char *message1 = "\nHello from thread 1\nGoodbye from thread1";
	const char *message2 = "\nHello from thread 2\nGoodbye from thread2";
	int iret1, iret2;

	// thread 1
	iret1 = pthread_create(&thread1, NULL, print_message_function, (void*) message1);

	if(iret1){
		fprintf(stderr, "Error: pthread create return code: %d\n", iret1);
		exit(EXIT_FAILURE);
	}

	pthread_join(thread1, NULL);

	// thread 2
	iret2 = pthread_create(&thread2, NULL, print_message_function, (void*) message2);

	if(iret2){
		fprintf(stderr, "Error: pthread create return code: %d\n", iret1);
		exit(EXIT_FAILURE);
	}

	pthread_join(thread2, NULL);

	exit(EXIT_SUCCESS);
}

void *print_message_function(void *ptr){

	char *message;
	message = (char *) ptr;
	printf("%s\n", message);
}

