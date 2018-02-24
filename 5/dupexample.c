#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <stdlib.h>
#include <string.h>

void exec1();
void exec2();

int pid;
int pipefd[2];

int main(void){
	
	printf("main");
	if(pipe(pipefd) == -1){
		perror("Error init pipe");
		exit(1);
	}
	else{
		printf("Calling exec1");
		exec1();
	}

	if((pid == fork()) == -1){
		perror("Error init fork 1");
		exit(1);
	}
	else if(pid == 0){
		printf("Calling exec2");
		exec2();
	}

	close(pipefd[0]);
	close(pipefd[1]);
}

void exec1(){
	printf("In exec1");

	dup2(pipefd[1], 1);

	close(pipefd[0]);
	close(pipefd[1]);

	execlp("ps", "ps", "aux", NULL);

	perror("Error with ps aux");
	exit(1);
}

void exec2(){

	printf("In exec2");
	dup2(pipefd[0], 0);

	close(pipefd[0]);
	close(pipefd[1]);

	execlp("grep", "grep", "login", NULL);

	perror("Error with grep login");
	exit(1);
}