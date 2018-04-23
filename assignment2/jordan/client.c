#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
	int SID;
	struct sockaddr_in server;
	char clientMessage[500];
	char serverMessage[500];
	char* file_name = "/home/jordan/Documents/htmlfiles/index.html";
	char file_buffer[512];

	//create socket
	SID = socket(AF_INET, SOCK_STREAM, 0);
	
	if(SID == -1)
	{
		printf("Error creating socket");
	}

	else
	{
		printf("socket created");
	}

	//Port to connect
	server.sin_port = htons(8082); 

	//server
	server.sin_addr.s_addr = inet_addr("127.0.0.1");

	//ipv4 protocol
	server.sin_family = AF_INET;

	if(connect(SID, (struct sockaddr *) &server, sizeof(server)) < 0)
	{

		printf("connect failed");
		return 1;
	}

	printf("Connected to server\n");

	printf("[Client] Sending %s to the server...", file_name);
	FILE *file_open = fopen(file_name, "r");
	bzero(file_buffer, 512);
	int block_size, i=0;

	while((block_size = fread(file_buffer, sizeof(char), 512, file_open)) > 0)
	{

		printf("Data sent %d = %d \n", i, block_size);
	
		if(send(SID, file_buffer, block_size, 0) < 0)
		{
			exit(1);
		}

		bzero(file_buffer, 512);
		i++;
	}

	close(SID);
	return 0;

}
