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

	if(argc < 2){
		printf("\nin null\n");

		char *arguments[] = {"ps", "-aux", NULL};
		execv("/bin/ps", arguments);

	}
	if(strcmp(argv[1], "search") == 0){
		printf("\nin search\n");

		char *search = argv[2];
		printf("\n%s\n", search);

		char *arguments[] = {"ps", "-aux", NULL};
		execv("/bin/ps", arguments);
	}
	else if(strcmp(argv[1], "kill") == 0){
		printf("\nin kill\n");

		int process = atoi(argv[2]);

		char *arguments[] = {"kill", argv[2], NULL};
		execv("/bin/kill", arguments);
	}
	// char *argv[] = {"kill", "2800", NULL};

	// execv("/bin/kill", argv);
	// printf("I shall not be executed");

	return 0;
}