#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <mqueue.h>

#define BUFFER_SIZE 1024

int main(){

	mqd_t mq;
	struct mq_attr queue_attributes;
	char buffer[BUFFER_SIZE + 1];
	int terminate = 0;

	queue_attributes.mq_flags = 0;
	queue_attributes.mq_maxmsg = 10;
	queue_attributes.mq_msgsize = BUFFER_SIZE;
	queue_attributes.mq_curmsgs = 0;


	mq = mq_open("/new_queue", O_CREAT | O_RDONLY, 0644, &queue_attributes);

	do{

		ssize_t bytes_read;

		bytes_read = mq_receive(mq, buffer, BUFFER_SIZE, NULL);

		// buffer[bytes_read] = '\0';

		if(! strncmp(buffer, "exit", strlen("exit"))){
			terminate = 1;
		}
		else{
			printf("Message: %s", buffer);
		}
	}
	while(!terminate);

	mq_close(mq);
	mq_unlink("/example_queue");
	return 0;
}