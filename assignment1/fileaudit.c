/*
starts audit and runs ausearch
ausearch -i will translate numbers of ID's to human-readable e.g. uid will show the name of the user
ausearch -ts today flag will only gather the audit logs of the day 
*/
#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <string.h>

#include <errno.h>
#include <sys/stat.h>
#include <sys/fcntl.h>

#include "date.h"
#include "messagequeue.h"

void createAuditLog(){

	pid_t cpid, w;
	int status;

	cpid = fork();
	if (cpid == -1) {
	    perror("fork");
	    exit(EXIT_FAILURE);
	}

	if (cpid == 0) {

		// Command execution in here         
		
	    printf("Child PID is %ld\n", (long) getpid());

		char dateBuffer[80];
	    char *date = getCurrentDate(dateBuffer);
	    char * fileType = ".txt";
	   
	    char *source = "/home/eamon/Documents/software/systems-software/assignment1/var/www/html/intranet/";
		
		// create path and file name of the timestamp of the log
		char *destination = "/home/eamon/Documents/software/systems-software/assignment1/auditlogs/";
		int newDestinationSize = strlen(destination) + strlen(date) + strlen(fileType) + 1;
		char * newBuffer = (char *)malloc(newDestinationSize);
		strcpy(newBuffer, destination);
		strcat(newBuffer, date);
		strcat(newBuffer, fileType);

		// Redirect output into log file in changelogs directory with time of log.
		int fd = open(newBuffer, O_RDWR | O_CREAT);
		dup2(fd, 1);
		dup2(fd, 2);
		close(fd);

		// ausearch only todays audit logs
		execlp("ausearch", "ausearch", "-i", "-ts", "today", "-f", source, NULL);

	} 
	else { 
		
		// Waits for the child process to exit and return its status code and sends
        // an appropriate info/error message back to the daemon to log
	    do {

	        w = waitpid(cpid, &status, WUNTRACED | WCONTINUED);
	        if (w == -1) {
				perror("waitpid");
				exit(EXIT_FAILURE);
			}

			if (WIFEXITED(status)) {
				
				printf("exited, status=%d\n", WEXITSTATUS(status));
	        }

	        if(status == 0){
	        	printf("Exited correctly\n");
	        	sendQueueMessage("INFO: ausearch file created");
	        }
	        else{
	        	sendQueueMessage("ERROR: AUSEARCH SYNC");
	        }
	    } while (!WIFEXITED(status) && !WIFSIGNALED(status));
	}
}

void startFileWatch(){

	char * directory = "/home/eamon/Documents/software/systems-software/assignment1/var/www/html/intranet/";

	pid_t cpid, w;
	int status;

	cpid = fork();
	
	if (cpid == -1) {
	    perror("fork");
	    exit(EXIT_FAILURE);
	}

	if (cpid == 0) { 

		// Command execution in here

	    printf("Child PID is %ld\n", (long) getpid());

		execlp("auditctl", "auditctl", "-w", directory, "-p", "rwxa", NULL);

	} 
	else { 

		// Waits for the child process to exit and return its status code and sends
        // an appropriate info/error message back to the daemon to log

	    do {

	        w = waitpid(cpid, &status, WUNTRACED | WCONTINUED);
	        if (w == -1) {
				perror("waitpid");
				exit(EXIT_FAILURE);
			}

			if (WIFEXITED(status)) {
				
				printf("exited, status=%d\n", WEXITSTATUS(status));
	        } 
	        else if (WIFSIGNALED(status)) {
	            
				printf("killed by signal %d\n", WTERMSIG(status));
	        } else if (WIFSTOPPED(status)) {
	            
				printf("stopped by signal %d\n", WSTOPSIG(status));
	        } else if (WIFCONTINUED(status)) {

				printf("continued\n");
	        }

	        if(status == 0){
	        	printf("auditctl Exited correctly\n");
	        	sendQueueMessage("INFO: audit started");
	        }
	        else{
	        	sendQueueMessage("ERROR: AUDITCTL");
	        }
	    } while (!WIFEXITED(status) && !WIFSIGNALED(status));
	}
}