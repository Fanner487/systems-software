#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <math.h>
#include <string.h>

#include "date.h"


int main(int argc, char **argv){

	// char *command = argv[1];
	// printf("\n%s\n", command);
	// char *arguments[] = {"cp", "-r", "/home/eamon/Documents/software/systems-software/assignment1/var/www/html/intranet", "/home/eamon/Documents/software/systems-software/assignment1/var/www/html/backup", 0};
	// execvp("/bin/cp", arguments);

	char *source = "/home/eamon/Documents/software/systems-software/assignment1/var/www/html/intranet";
	char *destination = "/home/eamon/Documents/software/systems-software/assignment1/var/www/html/backup";

	char dateBuffer[80];
	char *date = getCurrentDate(dateBuffer);

	int newSize = strlen(destination) + strlen(date) + 1;
	char *destinationWithDate = (char *)malloc(newSize);

	strcpy(destinationWithDate, destination);
	strcat(destinationWithDate, date);



	execlp("cp", "cp", "-r", source, destinationWithDate, NULL);


	printf("Should not be here");

	return 0;
}