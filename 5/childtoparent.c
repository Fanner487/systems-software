#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <stdlib.h>
#include <string.h>

int main(void){
	int fd[2], nbytes;
	pid_t pid;
	char string[] = "Hola mundo\n";
	char readbuffer[100];

	pipe(fd);

	pid = fork();

	if(pid == 0){

		// Child
		
		close(fd[0]);

		write(fd[1], string, strlen(string) + 1);
		exit(0);
	}
	else{

		// Parent

		close(fd[1]);

		nbytes = read(fd[0], readbuffer, sizeof(readbuffer));

		printf("Message from child is: %s", readbuffer);
	}
}