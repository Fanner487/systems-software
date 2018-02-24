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

		fp = popen("diff 1 2", "r");

		char string[4096];
		char c;

		char * buffer;
		long length;

		FILE *outputFile;
		outputFile = fopen("newLog.txt", "a+");




		// if(fp){
		// 	fseek(fp, 0, SEEK_END);
		// 	length = ftell(fp);
		// 	fseek(fp, 0, SEEK_SET);
		// 	buffer = malloc(length);

		// 	if(buffer){
		// 		fread(buffer, 1, length, fp);
		// 	}

		// 	fclose(fp);
		// }

		// if(buffer){
		// 	printf("%s", buffer);
		// }

		// while(fgets(path, 4096, fp) != NULL){
		// 	// printf("%s", path);

		// 	strcat(string, path);
			
		// }

		while((c = getc(fp)) != EOF){
			printf("%c", c);
			fputc(c, outputFile);
			// strcat(string, c);
		}

		status = pclose(fp);
		fclose(outputFile);
		// printf("%s", string);
// 
		write(fd[1], string, strlen(string) + 1);
		
		exit(0);
	}
}