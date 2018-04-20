#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>

void getCredentials(char *message){

	char username[500];
	char password[500];
	char folder[500];
	char file[500];
	char output[500];

	printf("Enter username: ");
	scanf("%s", username);
	printf("\n");

	printf("Enter password: ");
	scanf("%s", password);
	printf("\n");

	printf("Enter file: ");
	scanf("%s", file);
	printf("\n");

	printf("Enter destination folder: ");
	scanf("%s", folder);
	printf("\n");


	strcpy(message, username);
	strcat(message, " ");
	strcat(message, password);
	strcat(message, " ");
	strcat(message, file);
	strcat(message, " ");
	strcat(message, folder);
}

int main(int argc, char *argv[]){

	int SID;
	struct sockaddr_in server;
	char clientMessage[500];
	char serverMessage[500];
	char destinationFolder[500];

	char message[500];

	getCredentials(&message);	

	printf("\n%s\n", message);

	SID = socket(AF_INET, SOCK_STREAM, 0);

	if(SID == -1){
		printf("error creating socket\n");
	}
	else{
		printf("socket created\n");
	}

	server.sin_port = htons(8081);
	server.sin_addr.s_addr = inet_addr("127.0.0.1");
	server.sin_family = AF_INET;

	if(connect(SID, (struct sockaddr *)&server, sizeof(server)) < 0){
		printf("Connect failed\n");
		return 1;
	}

	printf("Connected to server");

	char *filename = "/home/eamon/Documents/software/systems-software/assignment2/test/clientfiles/file.txt";

	char fileBuffer[512];

	printf("Sending file to server\n");

	FILE *fileOpen = fopen(filename, "r");

	bzero(fileBuffer, 512);

	int blockSize, i = 0;

	if(send(SID, message, strlen(message), 0) < 0){
		printf("send failed\n");
		return 1;
	}

	// if(recv(SID, serverMessage, 500, 0) < 0){
	// 	printf("IO error\n");

	// 	// break;
	// }

	// while((blockSize = fread(fileBuffer, sizeof(char), 512, fileOpen)) > 0){
	// 	printf("Data sent %d = %d\n", i, blockSize);

	// 	if(send(SID, fileBuffer, blockSize, 0) < 0){
	// 		exit(1);
	// 	}

	// 	bzero(fileBuffer, 512);
	// 	i++;
	// }

	// while(1){

	// 	// printf("Enter message: \n");
	// 	// scanf("%s", clientMessage);

	// 	// if(send(SID, clientMessage, strlen(clientMessage), 0) < 0){
	// 	// 	printf("send failed\n");
	// 	// 	return 1;
	// 	// }

	// 	if(recv(SID, serverMessage, 500, 0) < 0){
	// 		printf("IO error\n");

	// 		break;
	// 	}

	// 	printf("\nServer sent: %s", serverMessage);
		
	// }

	close(SID);
	return 0;
}