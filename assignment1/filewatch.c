#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <signal.h>
#include <stdlib.h>
#include <syslog.h>
#include <sys/stat.h>
#include <time.h>
#include <string.h>

#include "date.h"

void makeAuditRecord(){
	char dateBuffer[80];

	char *date = getCurrentDate(dateBuffer);
	char * pathBeginning = "ausearch -f /home/eamon/Documents/software/systems-software/assignment1/var/www/html/ > /home/eamon/Documents/software/systems-software/assignment1/changelogs/";
	char * fileType = ".txt";

	int newSize = strlen(pathBeginning) + strlen(date) + strlen(fileType) + 1;
	char * newBuffer = (char *)malloc(newSize);

	strcpy(newBuffer, pathBeginning);
	strcat(newBuffer, date);
	strcat(newBuffer, fileType);

	FILE *fp;
	FILE *outputFile;
	int status;

	char readbuffer[1024];

	fp = popen(newBuffer,"r");
	outputFile = fopen("/home/eamon/Documents/software/systems-software/assignment1/auserchlog.txt", "a+");

	while(fgets(readbuffer, 1024,fp) != NULL){
		fprintf(outputFile, "%s", readbuffer);
	}

	status = pclose(fp);
}