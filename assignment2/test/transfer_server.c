#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <stdio.h>

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

	char file_buffer[512];
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
	server.sin_port = htons(8082);

	//use ipvv4 protocol
	server.sin_family = AF_INET;

	server.sin_addr.s_addr = INADDR_ANY;

	//bind
	
	if(bind(s,(struct sockaddr *)&server, sizeof(server)) < 0)
	{

		perror("Bind issue\n");
		return 1;
	}

	else
	{
		printf("Bind complete\n");

	}

	//listen for a connection
	listen(s,3);

	//accept and incoming connection
	printf("Waiting incoming connection form client>>\n");
	consize = sizeof(struct sockaddr_in);

	cs = accept(s, (struct sockaddr *) &client, (socklen_t*) &consize);

	if(cs < 0)
	{
		perror("Cant establish connection\n");
		return 1;
	}

	else
	{
		printf("Connection form client accepted\n");
	}

	FILE *file_open = fopen(file_name, "w");

	if(file_open == NULL)
		printf("File %s Cannot be opened file on server.\n", file_name);

	else{
		bzero(file_buffer, 512);
		int block_size = 0;
		int i = 0;
	
		while((block_size = recv(cs, file_buffer, 512, 0)) > 0)
		{

			printf("Data received %d = %d \n", i, block_size);
			int write_sz = fwrite(file_buffer, sizeof(char), block_size, file_open);
			bzero(file_buffer, 512);
			i++;
		}

	}

	printf("Transfer Complete!\n");
	fclose(file_open);

	if(READSIZE == 0)
	{
		puts("Client disconnected\n");
		fflush(stdout);
	}

	else if(READSIZE == -1)
	{

		perror("read error\n");
	}

	return 0;
}
