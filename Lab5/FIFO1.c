#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <fcntl.h>

#define MAX_BUF 1024

int main()
{

	int fd;
	char * fifoFile = "/home/jordan/Documents/Lab5/filoFile";
	char buf[MAX_BUF];

	fd = open(fifoFile, O_RDONLY);
	read(fd, buf, MAX_BUF);
	printf("Message in: %s\n", buf);
	close(fd);

	return 0;
}

