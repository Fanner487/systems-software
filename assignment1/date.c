#include <stdio.h>
#include <time.h>

char* getCurrentDate(char * buffer){
	printf("\nIn getCurrentDate");
	time_t rawTime;
	struct tm * timeinfo;
	time (&rawTime);
	timeinfo = localtime(&rawTime);
	strftime(buffer, 80, "%d_%m_%Y", timeinfo);

	printf("\nTime: %s", buffer);

	return buffer;
}
