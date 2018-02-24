#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <math.h>
#include <string.h>


int main(int argc, char **argv){

	// char *command = argv[1];
	// printf("\n%s\n", command);
	char *arguments[] = {"rsync", "-vr", "/home/eamon/Documents/software/systems-software/assignment1/var/www/html/intranet", "/home/eamon/Documents/software/systems-software/assignment1/var/www/html/live", 0};
	execvp("rsync", arguments);


	// char *argumentscp[] = {"mv", "-v", "/home/eamon/Documents/software/systems-software/assignment1/var/www/html/live/intranet/*", "/home/eamon/Documents/software/systems-software/assignment1/var/www/html/live/", 0};
	// execvp("/bin/cp", argumentscp);

	// char *argumentsrm[] = {"rm", "-rf", "/home/eamon/Documents/software/systems-software/assignment1/var/www/html/live/intranet/", 0};
	// execvp("/bin/rm", argumentsrm);

	// execl("/bin/cp", "-r", "/home/eamon/Documents/software/systems-software/assignment1/var/www/html/intranet", "/home/eamon/Documents/software/systems-software/assignment1/var/www/html/backup", 0);

	printf("Should not be here");

	return 0;
}