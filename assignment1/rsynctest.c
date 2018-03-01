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
	// char *arguments[] = {"rsync", "-vr", "/home/eamon/Documents/software/systems-software/assignment1/var/www/html/intranet", "/home/eamon/Documents/software/systems-software/assignment1/var/www/html/live", 0};
	// execvp("rsync", arguments);

	char *source = "/home/eamon/Documents/software/systems-software/assignment1/var/www/html/intranet/";
	char *destination = "/home/eamon/Documents/software/systems-software/assignment1/var/www/html/live/";

	execlp("rsync", "rsync", "-vr", source, destination, NULL);



	return 0;
}