#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/stat.h>
#include <arpa/inet.h>
#include <unistd.h>

void displayMessage(char *message){

	printf("\n--------------\n");
	printf("%s\n", message);
	printf("--------------\n\n");
}

void getCredentials(char *message){

	char username[500];
	char password[500];
	char output[500];

	displayMessage("Login");

	printf("Enter username: ");
	scanf("%s", username);
	printf("Enter password: ");
	scanf("%s", password);

	strcpy(message, username);
	strcat(message, " ");
	strcat(message, password);
}

void sendFile(int SID, char *filePath){
	
	char fileBuffer[512];
	FILE *fileOpen;
	fileOpen = fopen(filePath, "r");

	bzero(fileBuffer, 512);

	while((blockSize = fread(fileBuffer, sizeof(char), 512, fileOpen)) > 0){
		
		printf("Data sent %d = %d bytes\n", i, blockSize);
		if(send(SID, fileBuffer, blockSize, 0) < 0){
			exit(1);
		}

		bzero(fileBuffer, 512);
		i++;
	}
}

void getFilePathAndFolder(char *message, char *filePath){

	char *baseDirectory = "/home/eamon/Documents/software/systems-software/assignment2/test/clientfiles/";
	char folder[500];
	char file[500];

	printf("Enter file to backup: ");
	scanf("%s", &file);

	// Copies file path
	strcpy(filePath, baseDirectory);
	strcat(filePath, file);

	printf("%s\n", filePath);

	// Checks to see if file exists
	if(access(filePath, 0) != 0){
	
		displayMessage("File does not exist");
		exit(1);
	}

	printf("\n");
	printf("Enter destination folder\n");
	printf("(offers, marketing, sales, promotions): ");
	scanf("%s", folder);

	strcpy(message, file);
	strcat(message, " ");
	strcat(message, folder);
}

void handleResponse(int SID){

	char serverMessage[500];

	if(recv(SID, serverMessage, 500, 0) < 0){
		printf("IO error\n");
		// break;
	}

	if(strcmp(serverMessage, "user authenticated") == 0){
		displayMessage("User authenticated. Connected to server");
	}
	else if(strcmp(serverMessage, "START_TRANSFER") == 0){
		displayMessage("Starting transfer")
	}
	else if(strcmp(serverMessage, "BACKUP_COMPLETE") == 0){
		displayMessage("Backup complete")
	}
	else{
		displayMessage(serverMessage);
		return 1;
	}
}

int main(int argc, char *argv[]){

	int SID;
	struct sockaddr_in server;
	char clientMessage[500];
	char serverMessage[500];
	char destinationFolder[500];	

	SID = socket(AF_INET, SOCK_STREAM, 0);

	if(SID == -1){
		printf("error creating socket\n");
	}
	else{
		printf("socket created\n\n");
	}

	server.sin_port = htons(8081);
	server.sin_addr.s_addr = inet_addr("127.0.0.1");
	server.sin_family = AF_INET;

	if(connect(SID, (struct sockaddr *)&server, sizeof(server)) < 0){
		printf("Connect failed\n");
		return 1;
	}

	int blockSize, i = 0;

	char loginCredentials[500];

	getCredentials(&loginCredentials);	


	if(send(SID, loginCredentials, strlen(loginCredentials), 0) < 0){
		printf("send failed\n");
		return 1;
	}

	memset(serverMessage, 0, 500);

	handleResponse(SID);

	char fileFolderMessage[500];
	char filePath[500];

	getFilePathAndFolder(&fileFolderMessage, &filePath);	

	if(send(SID, fileFolderMessage, strlen(fileFolderMessage), 0) < 0){
		printf("send failed\n");
		return 1;
	}

	memset(serverMessage, 0, 500);

	if(recv(SID, serverMessage, 500, 0) < 0){
		printf("IO error\n");
		// break;
	}

	// Handle response for START_TRANSFER
	handleResponse(SID);

	sendFile(SID, filePath);

	handleResponse(SID);

	close(SID);
	return 0;
}