/*
Sends message to the message queue in main
*/
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <mqueue.h>

#define BUFFER_SIZE 1024

void sendQueueMessage(char * message){

	mqd_t mq;
	mq = mq_open("/assignment_one_queue", O_WRONLY);
	mq_send(mq, message, BUFFER_SIZE, 0);
	mq_close(mq);
}