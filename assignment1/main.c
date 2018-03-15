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
#include <signal.h>
#include <time.h>

#include "backup.h"
#include "syncfiles.h"
#include "permissions.h"
#include "log.h"
#include "filewatch.h"
#include "date.h"

#define BUFFER_SIZE 1024

void doBackup(){
	printf("Backing up now\n");
	// setFilePermissions("1111");
	lockSite();
	backup();
	syncFiles();
	makeAuditRecord();
	logInfo("Back and sync completed");
	// setFilePermissions("0777");
	unlockSite();
}

void createDaemon(){
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
}

void sig_handler(int sigNum){
	if(sigNum == SIGINT){
		logInfo("SIGNAL INTERRUPT CALLED");
		printf("Signal interrupt\n");
		printf("Backing up now\n");
		setFilePermissions("1111");
		backup();
		syncFiles();
		logInfo("MANUAL backup and sync");
		setFilePermissions("0777");
	}
}

void runScheduledBackup(int argc, char **argv){

	printf("\n\n In child fork PARENT");

	int hour;
	int minute;

	// If no arguments specified in command line, 11pm will be used for backup time
	printf("\n\nargc size: %d", argc);
	if (argc < 3){
		hour = 23;
		minute = 0;
	}
	else{
		hour = atoi(argv[1]);
		minute = atoi(argv[2]);
	}

	

	time_t now;
    struct tm newyear;
    double seconds;
    time(&now);   //get current time; same as: now = time(NULL)  
    newyear = *localtime(&now);
    newyear.tm_hour = hour; 
    newyear.tm_min = minute; 
    newyear.tm_sec = 0;			

	while(1){
		sleep(1);
		time(&now);
		seconds = difftime(now,mktime(&newyear));

		printf("\n%.f", seconds);

		if(seconds >= 0){

			doBackup();

			newyear.tm_mday += 1;
		}
	}
}

void runMessageQueue(){
	mqd_t mq;
	struct mq_attr queue_attributes;
	char buffer[BUFFER_SIZE + 1];
	int terminate = 0;

	queue_attributes.mq_flags = 0;
	queue_attributes.mq_maxmsg = 10;
	queue_attributes.mq_msgsize = BUFFER_SIZE;
	queue_attributes.mq_curmsgs = 0;

	mq = mq_open("/assignment_one_queue", O_CREAT | O_RDONLY, 0644, &queue_attributes);

	// Interruption handler
	if(signal(SIGINT, sig_handler) == SIG_ERR){
		printf("Something went wrong\n");
		logInfo("ERROR: SIG_HANDLER");
	}


	do{
		ssize_t bytes_read;

		bytes_read = mq_receive(mq, buffer, BUFFER_SIZE, NULL);
		logInfo(buffer);

		buffer[bytes_read] = '\0';

		// printf("Message: %s\nSize: %d\n", buffer, strlen(buffer));

		if(! strncmp(buffer, "exit", strlen("exit"))){
			terminate = 1;
			printf("\n\nchild exit received");
			logInfo("Exited Daemon");
		}
		else if (! strncmp(buffer, "backup", strlen("backup"))){
			doBackup();
		}
	}
	while(terminate < 1);

	printf("\nExiting child");
}



int main (int argc, char **argv) {

	// char * start_filewatch = " auditctl -w /home/eamon/Documents/software/systems-software/assignment1/var/www/html/ -p rwxa";
	

	// FILE *fp;
	// FILE *outputFile;

	// char readbuffer[1024];

	// fp = popen(start_filewatch,"r");
	// outputFile = fopen("/home/eamon/Documents/software/systems-software/assignment1/auditlog.txt", "a+");

	// while(fgets(readbuffer, 1024,fp) != NULL){
	// 	fprintf(outputFile, "%s", readbuffer);
	// }

	// pclose(fp);

	startFileWatch();

	// printf("\nProgram is running.");

	int pid = fork();


	// Parent
	if(pid > 0){

		sleep(10);
		logInfo("Exited parent");
		exit(EXIT_SUCCESS);
	}
	else if(pid == 0){


		createDaemon();

	
		int childForkPid = fork();


		if(childForkPid > 0){

			runScheduledBackup(argc, argv);

			// printf("\n\n In child fork PARENT");

			// int hour;
			// int minute;

			// // If no arguments specified in command line, 11pm will be used for backup time
			// if (argc < 3){
			// 	hour = 23;
			// 	minute = 0;
			// }
			// else{
			// 	hour = atoi(argv[1]);
			// 	minute = atoi(argv[2]);
			// }

			

			// time_t now;
		 //    struct tm newyear;
		 //    double seconds;
		 //    time(&now);   //get current time; same as: now = time(NULL)  
		 //    newyear = *localtime(&now);
		 //    newyear.tm_hour = hour; 
		 //    newyear.tm_min = minute; 
		 //    newyear.tm_sec = 0;			

			// while(1){
			// 	sleep(1);
			// 	time(&now);
			// 	seconds = difftime(now,mktime(&newyear));

			// 	printf("\n%.f", seconds);

			// 	if(seconds >= 0){

			// 		doBackup();

			// 		newyear.tm_mday += 1;
			// 	}
			// }


			return 0;

			// Schedule backup here
		}
		else if (childForkPid == 0){

			printf("\n\n In child fork CHILD");

			runMessageQueue();

			// mqd_t mq;
			// struct mq_attr queue_attributes;
			// char buffer[BUFFER_SIZE + 1];
			// int terminate = 0;

			// queue_attributes.mq_flags = 0;
			// queue_attributes.mq_maxmsg = 10;
			// queue_attributes.mq_msgsize = BUFFER_SIZE;
			// queue_attributes.mq_curmsgs = 0;

			// mq = mq_open("/assignment_one_queue", O_CREAT | O_RDONLY, 0644, &queue_attributes);

			// // Interruption handler
			// if(signal(SIGINT, sig_handler) == SIG_ERR){
			// 	printf("Something went wrong\n");
			// 	logInfo("ERROR: SIG_HANDLER");
			// }


			// do{
			// 	ssize_t bytes_read;

			// 	bytes_read = mq_receive(mq, buffer, BUFFER_SIZE, NULL);
			// 	logInfo(buffer);

			// 	buffer[bytes_read] = '\0';

			// 	// printf("Message: %s\nSize: %d\n", buffer, strlen(buffer));

			// 	if(! strncmp(buffer, "exit", strlen("exit"))){
			// 		terminate = 1;
			// 		printf("\n\nchild exit received");
			// 		logInfo("Exited Daemon");
			// 	}
			// 	else if (! strncmp(buffer, "backup", strlen("backup"))){
			// 		doBackup();
			// 	}
			// }
			// while(terminate < 1);

			// printf("\nExiting child");

			return 0;
		}
	}

	return 0;
}

