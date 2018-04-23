#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <stdio.h>


// void transfer()


void *clientHandler(void *cs){

	printf("In client handler\n");
	char fileBuffer[512];
	char destinationFolder[512];

	int clientSocket = *(int *) cs;

	bzero(fileBuffer, 512);
	bzero(destinationFolder, 512);

	char username[500];
	char password[500];
	char file[500];
	char folder[500];

	printf("Ready to receive\n");

	recv(clientSocket, destinationFolder, 512, 0);
	printf("Received message: %s\n", destinationFolder);
	sscanf(destinationFolder, "%s %s", username, password);
		// printf("username: %s\nPassword: %s\n", u, p);

	printf("%s\n", username);
	printf("%s\n", password);


	if(authenticate(username, password) == 1){
		printf("user is authenticated\n");
		write(clientSocket, "user authenticated", strlen("user authenticated") + 1);

	}
	else{
		printf("not a valid user\n");
		write(clientSocket, "Login denied", strlen("not a valid user") + 1);
		return 1;
	}

	recv(clientSocket, destinationFolder, 512, 0);
	sscanf(destinationFolder, "%s %s", file, folder);

	printf("%s\n", file);
	printf("%s\n", folder);

	if(
		strcmp(folder, "marketing") != 0 &&
		strcmp(folder, "offers") != 0 &&
		strcmp(folder, "sales") != 0 &&
		strcmp(folder, "promotions") != 0 ){

		write(clientSocket, "Not a valid folder option", strlen("Not a valid folder option") + 1);
		return 1;
	}

	
	bzero(destinationFolder, 512);

	char *baseDirectory = "/home/eamon/Documents/software/systems-software/assignment2/test/serverfiles/";
	char outputFilePath[500];

	strcpy(outputFilePath, baseDirectory);
	strcat(outputFilePath, folder);
	strcat(outputFilePath, "/");
	strcat(outputFilePath, file);

	FILE *outputFile;

	outputFile = fopen(outputFilePath, "w");

	int blockSize = 0;

	write(clientSocket, "START_TRANSFER", strlen("START_TRANSFER") + 1);
	
	// recv(cs?, fileBuffer, 512, 0);

	// printf("%s\n", fileBuffer);
	while((blockSize = recv(clientSocket, fileBuffer, 512, 0)) > 0)
	{
	
		printf("Data received. %d\n", blockSize);
		int write_sz = fwrite(fileBuffer, sizeof(char), blockSize, outputFile);
		bzero(destinationFolder, 512);

		memset(fileBuffer, 0, sizeof(fileBuffer));

		if(write_sz == 0 || write_sz != 512){
			break;
		}
		// break;
	}

	fclose(outputFile);

	write(clientSocket, "BACKUP_COMPLETE", strlen("BACKUP_COMPLETE") + 1);
}

int authenticate(char *username, char *password){

	FILE *userFile;
	userFile = fopen("users.txt", "r");
	
	char u[500];
	char p[500];
	
	int authenticated = 0;

	while(fscanf(userFile, "%s %s", u, p) != EOF){
	// printf("username: %s\nPassword: %s\n", u, p);

		if(strcmp(username, u) == 0 && strcmp(password, p) == 0){
			authenticated = 1;
			return 1;
		}
	}

	if(authenticated == 1){
		
		fclose(userFile);
		return 1;
	}
	else{
		fclose(userFile);
		return 0;
	}
}

int main(int argc, char *argv[])
{
	//socket descripter
	int s;

	//client socket
	int cs;

	//struct size
	int consize;

	//size of sockaddr_in for client connection
	int READSIZE;

	struct sockaddr_in server, client;
	char message[500];

	
	char* file_name = "/home/eamon/Documents/software/systems-software/assignment2/test/serverfiles/file.txt";

	//Creating socket
	s = socket(AF_INET, SOCK_STREAM, 0);

	if ( s== -1 )
	{
		printf("Cloud not create socket\n");
	}
	
	else
	{	
		printf("Socket created successfully\n");
	}

	//port for communication
	server.sin_port = htons(8081);
	server.sin_family = AF_INET;
	server.sin_addr.s_addr = INADDR_ANY;

	//bind
	
	if(bind(s,(struct sockaddr *)&server, sizeof(server)) < 0){

		perror("Bind issue\n");
		return 1;
	}
	else{
		printf("Bind complete\n");

	}

	//listen for a connection
	listen(s,3);

	//accept and incoming connection
	printf("Waiting incoming connection form client>>\n");
	consize = sizeof(struct sockaddr_in);

	while(cs = accept(s, (struct sockaddr *) &client, (socklen_t*) &consize)){
			if(cs < 0)
		{
			perror("Cant establish connection\n");
			return 1;
		}
		else
		{
			printf("Connection form client accepted\n");

			pthread_t thread;

			// Allocates memory for client socket
			int *clientSocket = malloc(200);
			*clientSocket = cs;

			// int clientSocket = cs;
			if(pthread_create(&thread, NULL, clientHandler, (void *) clientSocket) < 0){
				perror("Failed to create thread for client");
			}
		}
	}

	return 0;
}
