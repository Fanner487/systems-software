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
	// char *arguments[] = {"cp", "a", "/home/eamon/Documents/software/systems-software/assignment1/var/www/html/intranet", "/home/eamon/Documents/software/systems-software/assignment1/var/www/html/backup"};
	// execvp("/bin/cp", arguments);

	execl("/bin/cp", "-a", "/home/eamon/Documents/software/systems-software/assignment1/var/www/html/intranet", "/home/eamon/Documents/software/systems-software/assignment1/var/www/html/backup", (char *)0);

	printf("Should not be here");

	return 0;
}