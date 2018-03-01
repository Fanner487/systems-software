#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <math.h>
#include <string.h>

#include "date.h"


void backup(){

	printf("\nIn backup\n");

	char *baseCommand = "cp -r ";
	char *source = "/home/eamon/Documents/software/systems-software/assignment1/var/www/html/intranet/ ";
	char *destination = "/home/eamon/Documents/software/systems-software/assignment1/var/www/html/backup/";

	char dateBuffer[80];
	char *date = getCurrentDate(dateBuffer);

	printf("\nDate: %s", date);

	int newDestinationSize = strlen(destination) + strlen(date) + 1;
	char *destinationWithDate = (char *)malloc(newDestinationSize);

	strcpy(destinationWithDate, destination);
	strcat(destinationWithDate, date);


	int commandSize = strlen(baseCommand) + strlen(source) + strlen(destinationWithDate) + 1;
	char *command = (char *)malloc(commandSize);

	strcpy(command, baseCommand);
	strcat(command, source);
	strcat(command, destinationWithDate);
	// execlp("cp", "cp", "-r", source, destinationWithDate, NULL);


	FILE *fp;
	FILE *outputFile;
	int status;
	char readbuffer[1024];

	fp = popen(command, "r");
	outputFile = fopen("/home/eamon/Documents/software/systems-software/assignment1/backuplog.txt", "a+");

	while(fgets(readbuffer, 1024,fp) != NULL){
		fprintf(outputFile, "%s", readbuffer);
	}

	status = pclose(fp);

	// return 0;
}