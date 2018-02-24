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
	char *arguments[] = {"chmod", "777", "log.txt", NULL};
	execv("/bin/chmod", arguments);

	printf("Should not be here");

	return 0;
}