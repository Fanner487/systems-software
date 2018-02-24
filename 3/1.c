#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main(){

	char *argv[] = {"ls", "-lah", NULL};

	execv("/bin/ls", argv);
	printf("I shall not be executed");

	return 0;
}
