/*
starts audit and runs ausearch
ausearch -i will translate numbers of ID's to human-readable e.g. uid will show the name of the user
ausearch -ts today flag will only gather the audit logs of the day 
*/
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
#include "log.h"

void makeAuditRecord(){
	
	char dateBuffer[80];

	// Creates a file with the date of the backup with all the change logs from ausearch inside the changelogs folder
	char *date = getCurrentDate(dateBuffer);
	char * pathBeginning = "ausearch -i -ts today -f /home/eamon/Documents/software/systems-software/assignment1/var/www/html/intranet/ > /home/eamon/Documents/software/systems-software/assignment1/changelogs/";
	char * fileType = ".txt";

	int newSize = strlen(pathBeginning) + strlen(date) + strlen(fileType) + 1;
	char * newBuffer = (char *)malloc(newSize);

	strcpy(newBuffer, pathBeginning);
	strcat(newBuffer, date);
	strcat(newBuffer, fileType);

	FILE *fp;
	FILE *outputFile;

	char readbuffer[1024];

	fp = popen(newBuffer,"r");
	outputFile = fopen("/home/eamon/Documents/software/systems-software/assignment1/auserchlog.txt", "a+");

	while(fgets(readbuffer, 1024,fp) != NULL){
		fprintf(outputFile, "%s", readbuffer);
	}

	logInfo("Watch file created");

	pclose(fp);
}

void startFileWatch(){

	char * start_filewatch = " auditctl -w /home/eamon/Documents/software/systems-software/assignment1/var/www/html/intranet/ -p rwxa";
	

	FILE *fp;
	FILE *outputFile;

	char readbuffer[1024];

	fp = popen(start_filewatch,"r");
	outputFile = fopen("/home/eamon/Documents/software/systems-software/assignment1/auditlog.txt", "a+");

	while(fgets(readbuffer, 1024,fp) != NULL){
		fprintf(outputFile, "%s", readbuffer);
	}

	logInfo("Started file watch");

	pclose(fp);
}