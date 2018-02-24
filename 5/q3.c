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

	FILE *fp;
	int status;
	char path[4096];

	pipe(fd);

	pid = fork();

	if(pid == 0){

		// Child
		
		close(fd[1]);

		nbytes = read(fd[0], readbuffer, sizeof(readbuffer));

		printf("Message from parent is: %s", readbuffer);

	}
	else{

		// Parent

		close(fd[0]);

		fp = popen("ls -lah", "r");

		char string[4096];
		char c;

		// while(fgets(path, 4096, fp) != NULL){
		// 	// printf("%s", path);

		// 	strcat(string, path);
			
		// }

		while((c = getc(fp)) != EOF){
			printf("%c", c);
			// strcat(string, c);
		}

		status = pclose(fp);
		// printf("%s", string);
// 
		write(fd[1], string, strlen(string) + 1);
		
		exit(0);
	}
}