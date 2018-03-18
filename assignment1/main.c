#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <unistd.h>
#include <sys/stat.h>
#include <setjmp.h>
#include <mqueue.h>
#include <signal.h>
#include <time.h>

#include "backup.h"
#include "syncfiles.h"
#include "permissions.h"
#include "log.h"
#include "fileaudit.h"
#include "date.h"
#include "messagequeue.h"


#define BUFFER_SIZE 1024

void doBackup(){
	printf("Backing up now\n");
	lockSite();
	backup();
	syncFiles();
	createAuditLog();
	unlockSite();
	logInfo("INFO: Back and sync completed");
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

void runScheduledBackup(int argc, char **argv){

	int hour;
	int minute;

	// If no arguments specified in command line, 11pm will be used for backup time
	if (argc < 3){
		hour = 23;
		minute = 0;
	}
	else{
		hour = atoi(argv[1]);
		minute = atoi(argv[2]);
	}

	time_t now;
    struct tm scheduleTime;
    double seconds;
    time(&now);
    scheduleTime = *localtime(&now);
    scheduleTime.tm_hour = hour; 
    scheduleTime.tm_min = minute; 
    scheduleTime.tm_sec = 0;	
	
	// Sleeps for a second, calculates time difference
	// Backup when it reaches 0 then increment scheduled back up day by 1
	while(1){

		sleep(1);
		time(&now);
		seconds = difftime(now,mktime(&scheduleTime));

		printf("\n%.f", seconds);

		if(seconds >= 0){

			doBackup();

			scheduleTime.tm_mday += 1;
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

	do{
		ssize_t bytes_read;

		bytes_read = mq_receive(mq, buffer, BUFFER_SIZE, NULL);

		buffer[bytes_read] = '\0';

		// Manual backup is intercepted here
		// Otherwise, all messages sent to queue is logged
		if(! strncmp(buffer, "exit", strlen("exit"))){
			terminate = 1;
			printf("\n\nchild exit received");
			logInfo("Exited Daemon");
		}
		else if (! strncmp(buffer, "backup", strlen("backup"))){
			doBackup();
		}
		else{
			logInfo(buffer);
		}
	}
	while(terminate < 1);

	printf("\nExiting child");
}

int main (int argc, char **argv) {

	startFileWatch();
	setFolderPermissions();

	int pid = fork();

	// Parent
	if(pid > 0){

		sleep(1);
		logInfo("Exited parent");
		exit(EXIT_SUCCESS);
	}
	else if(pid == 0){

		createDaemon();
	
		int childForkPid = fork();

		// Fork to run backup scheduling and message queue handling
		if(childForkPid > 0){

			runScheduledBackup(argc, argv);

			return 0;

			// Schedule backup here
		}
		else if (childForkPid == 0){

			printf("\n\n In child fork CHILD");

			runMessageQueue();

			return 0;
		}
	}

	return 0;
}