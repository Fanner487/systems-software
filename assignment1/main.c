#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <errno.h>
#include <unistd.h>
#include <sys/stat.h>
#include <syslog.h>
#include <setjmp.h>
#include <mqueue.h>

#include "backup.h"
#include "syncfiles.h"
#include "permissions.h"
#include "log.h"
#include "filewatch.h"

#define BUFFER_SIZE 1024

void main (int argc, char **argv) {

	char * start_filewatch = " auditctl -w /home/eamon/Documents/software/systems-software/assignment1/var/www/html/ -p rwxa";
	

	FILE *fp;
	FILE *outputFile;
	int status;

	char readbuffer[1024];

	fp = popen(start_filewatch,"r");
	outputFile = fopen("/home/eamon/Documents/software/systems-software/assignment1/auditlog.txt", "a+");

	while(fgets(readbuffer, 1024,fp) != NULL){
		fprintf(outputFile, "%s", readbuffer);
	}

	status = pclose(fp);



	printf("\nProgram is running.");

	int pid = fork();

	// mqd_t mq;
	// struct mq_attr queue_attributes;
	// char buffer[BUFFER_SIZE + 1];
	// int terminate = 0;

	// queue_attributes.mq_flags = 0;
	// queue_attributes.mq_maxmsg = 10;
	// queue_attributes.mq_msgsize = BUFFER_SIZE;
	// queue_attributes.mq_curmsgs = 0;

	// mq = mq_open("/example_queue", O_CREAT | O_RDONLY, 0644, &queue_attributes);

	// Parent
	if(pid > 0){

		printf("Parent process");
		sleep(10);
		exit(EXIT_SUCCESS);
	}
	else if(pid == 0){

		printf("Child process");

		if(setsid() < 0 ){
			exit(EXIT_FAILURE);
		}

		umask(0);

		if(chdir("/") < 0){
			exit(EXIT_FAILURE);
		}

		int x;

		for(x = sysconf(_SC_OPEN_MAX); x >= 0; x--){
			close(x);
		}


		// do{
		// 	ssize_t bytes_read;

		// 	bytes_read = mq_receive(mq, buffer, BUFFER_SIZE, NULL);

		// 	buffer[bytes_read] = '\0';

		// 	if(! strncmp(buffer, "exit", strlen("exit"))){
		// 		terminate = 1;
		// 	}
		// 	else if (! strncmp(buffer, "backup", strlen("backup"))){
		// 		setFilePermissions("1111");
		// 		backup();
		// 		syncFiles();
		// 		logInfo("Back and sync completed");
		// 		setFilePermissions("0777");
		// 	}

		// }
		// while(!terminate);

		setFilePermissions("1111");
		makeAuditRecord();
		backup();
		syncFiles();
		logInfo("Back and sync completed");
		setFilePermissions("0777");
		
	}

}
