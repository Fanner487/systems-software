#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(){

	int pid = fork();

	// Parent
	if(pid > 0){

		printf("Parent process");
		sleep(10);
		exit(EXIT_SUCCESS);
	}
	else if(pid == 0){

		printf("Child process");

		if(setsid() < 0 ){
			exit(EXIT_FAILURE);
		}

		umask(0);

		if(chdir("/") < 0){
			exit(EXIT_FAILURE);
		}

		int x;

		for(x = sysconf(_SC_OPEN_MAX); x >= 0; x--){
			close(x);
		}

		char *input[100];
		char buffer[256];
		FILE *fptr;

		fptr = fopen("/home/eamon/Documents/software/4/log.txt", "a+");

		int i = 0;

	

		

		while(1){
			sleep(1);
			fprintf(fptr, "%d\n", i);
			i++;

			if(i == 3){
				break;
			}
			// if(i)
		}

		fclose(fptr);
	}
}