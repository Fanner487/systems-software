#include <sys/types.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <unistd.h>

main(int argc, char *argv[])
{
	pid_t cpid, w;
	int status;

	cpid = fork();
	if (cpid == -1) {
	    perror("fork");
	    exit(EXIT_FAILURE);
	}

	if (cpid == 0) {            /* Code executed by child */
	    printf("Child PID is %ld\n", (long) getpid());
	    

	    char *source = "/home/eamon/Documents/software/systems-software/assignment1/var/www/html/intranet/";
		char *destination = "/ome/eamon/Documents/software/systems-software/assignment1/var/www/html/live/";
		// char *command = "rsync -r /home/eamon/Documents/software/systems-software/assignment1/var/www/html/intranet/ /home/eamon/Documents/software/systems-software/assignment1/var/www/html/live/";

		execlp("rsync", "rsync", "-r", source, destination, NULL);

	} 
	else {                    /* Code executed by parent */
	    do {
	        w = waitpid(cpid, &status, WUNTRACED | WCONTINUED);
	        if (w == -1) {
	            perror("waitpid");
	            exit(EXIT_FAILURE);
	        }

	       if (WIFEXITED(status)) {
	            printf("exited, status=%d\n", WEXITSTATUS(status));
	        } else if (WIFSIGNALED(status)) {
	            printf("killed by signal %d\n", WTERMSIG(status));
	        } else if (WIFSTOPPED(status)) {
	            printf("stopped by signal %d\n", WSTOPSIG(status));
	        } else if (WIFCONTINUED(status)) {
	            printf("continued\n");
	        }

	        if(status == 0){
	        	printf("Exited correctly\n");
	        }
	    } while (!WIFEXITED(status) && !WIFSIGNALED(status));

	    printf("Outside loop");
	    exit(EXIT_SUCCESS);
	}
}