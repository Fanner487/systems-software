/*
Allows user to explictly instruct the daemon to run the backup
'backup' is the command
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <mqueue.h>

#define BUFFER_SIZE 1024

int main(int argc, char **argv){

	mqd_t mq;
	char buffer[BUFFER_SIZE];
	char * message = argv[1];

	mq = mq_open("/assignment_one_queue", O_WRONLY);

	mq_send(mq, message, BUFFER_SIZE, 0);

	mq_close(mq);

	return 0;
}