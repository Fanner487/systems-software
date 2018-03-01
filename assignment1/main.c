#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <errno.h>
#include <unistd.h>
#include <sys/stat.h>
#include <syslog.h>
#include <setjmp.h>

#include "backup.h"
#include "syncfiles.h"

void main (int argc, char **argv) {
  printf("\nProgram is running.");

  int pid = fork();

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

		// backup();
		syncFiles();
		backup();

		// char *source = "/home/eamon/Documents/software/systems-software/assignment1/var/www/html/intranet/";
		// char *destination = "/home/eamon/Documents/software/systems-software/assignment1/var/www/html/live/";
		// // char *command = "rsync -vr /home/eamon/Documents/software/systems-software/assignment1/var/www/html/intranet/ /home/eamon/Documents/software/systems-software/assignment1/var/www/html/live/";

		// execlp("rsync", "rsync", "-vr", source, destination, NULL);
	}

}
