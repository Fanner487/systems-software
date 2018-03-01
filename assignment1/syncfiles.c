#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <math.h>
#include <string.h>

#include "date.h"


void syncFiles(){

	char *source = "/home/eamon/Documents/software/systems-software/assignment1/var/www/html/intranet/";
	char *destination = "/home/eamon/Documents/software/systems-software/assignment1/var/www/html/live/";
	char *command = "rsync -r /home/eamon/Documents/software/systems-software/assignment1/var/www/html/intranet/ /home/eamon/Documents/software/systems-software/assignment1/var/www/html/live/";

	// execlp("rsync", "rsync", "-r", source, destination, NULL);

	system(command);

}

