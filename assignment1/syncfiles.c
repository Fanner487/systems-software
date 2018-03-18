/*
Syncs files between intranet and live using rsync
*/
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <math.h>
#include <string.h>

#include "date.h"
#include "messagequeue.h"

void syncFiles(){

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
	    
	    char *source = "/home/eamon/Documents/software/systems-software/assignment1/var/www/html/intranet/";
		char *destination = "/home/eamon/Documents/software/systems-software/assignment1/var/www/html/live/";
		execlp("rsync", "rsync", "-r", source, destination, NULL);

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
	        	sendQueueMessage("INFO: Files synced");
	        }
	        else{
	        	sendQueueMessage("ERROR: FILE SYNC");
	        }

	    }
	    while (!WIFEXITED(status) && !WIFSIGNALED(status));
	}
}