#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <fcntl.h>

int main()
{

	int fd;
	char * fifoFile = "/home/jordan/Documents/Lab5/filoFile";

	//create the FIFO (name pipe)
	mkfifo(fifoFile, 0666);

	fd = open(fifoFile, O_WRONLY);
	write(fd,"The truth is out there!!", sizeof("The truth is out there!!"));
	close(fd);

	unlink(fifoFile);

	return 0;
}
