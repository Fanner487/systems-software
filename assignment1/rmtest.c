#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <math.h>
#include <string.h>


int main(int argc, char **argv){



	char *argumentsrm[] = {"rm", "-rf", "/home/eamon/Documents/software/systems-software/assignment1/var/www/html/live/intranet/", 0};
	execvp("/bin/rm", argumentsrm);

	// execl("/bin/cp", "-r", "/home/eamon/Documents/software/systems-software/assignment1/var/www/html/intranet", "/home/eamon/Documents/software/systems-software/assignment1/var/www/html/backup", 0);

	printf("Should not be here");

	return 0;
}