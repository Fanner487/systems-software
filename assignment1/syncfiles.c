#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <math.h>
#include <string.h>


void syncFiles(){

	char *source = "/home/eamon/Documents/software/systems-software/assignment1/var/www/html/intranet/";
	char *destination = "/home/eamon/Documents/software/systems-software/assignment1/var/www/html/live/";

	execlp("rsync", "rsync", "-vr", source, destination, NULL);

	return 0;
}