#include <stdio.h>
#include <stdlib.h>

int main(int argc, char **argv){

	char *filename = "/home/eamon/Documents/software/systems-software/assignment2/test/clientfiles/file.txt";

	char fileBuffer[512];

	printf("Sending file to server\n");

	FILE *fileOpen = fopen(filename, "r");

	bzero(fileBuffer, 512);

	int blockSize, i = 0;

	while((blockSize = fread(fileBuffer, sizeof(char), 512, fileOpen)) > 0){
		printf("Data sent %d = %d\n", i, blockSize);

		if(send(SID))
	}
}

