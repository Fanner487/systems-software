#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>

int main(int argc, char *argv[]){

	int authenticated = 0;
	FILE *fp;
	int i = 0;
	int c;
	char *username = argv[1];
	char *password = argv[2];

	char u[100];
	char p[100];


	fp = fopen("users.txt", "r");

	
	while(fscanf(fp, "%s %s", u, p) != EOF){
		// printf("username: %s\nPassword: %s\n", u, p);

		if(strcmp(username, u) == 0 && strcmp(password, p) == 0){
			authenticated = 1;
		}
	}

	if(authenticated == 1){
		printf("User authenticated\n");
	}
	else{
		printf("not valid\n");
	}


	
	fclose(fp);
}