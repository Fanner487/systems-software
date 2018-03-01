#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <stdlib.h>
#include <string.h>

int main ()
{
	FILE *fp;
	int status;
	char string[] = "Wasssuppp mate!\n";
	char readbuffer[1024];

	fp = popen("ls *","r");

	while(fgets(readbuffer, 1024,fp) != NULL)
		printf("%s", readbuffer);

	status = pclose(fp);
} 
