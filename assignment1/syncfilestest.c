#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <math.h>
#include <string.h>

// #include ""
void main(){

	char *source = "/home/eamon/Documents/software/systems-software/assignment1/var/www/html/intranet/";
	char *destination = "/home/eamon/Documents/software/systems-software/assignment1/var/www/html/live/";
	char *command = "rsync -vr /home/eamon/Documents/software/systems-software/assignment1/var/www/html/intranet/ /home/eamon/Documents/software/systems-software/assignment1/var/www/html/live/";

	// execlp("rsync", "rsync", "-vr", source, destination, NULL);


	FILE *fp;
	FILE *outputFile;
	int status;
	char string[] = "Wasssuppp mate!\n";
	char readbuffer[1024];

	fp = popen(command,"r");
	outputFile = fopen("/home/eamon/Documents/software/systems-software/assignment1/synclog.txt", "a+");

	while(fgets(readbuffer, 1024,fp) != NULL){
		fprintf(outputFile, "%s", readbuffer);
	}

	status = pclose(fp);
	pclose(outputFile);
}