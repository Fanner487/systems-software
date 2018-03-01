#include <stdio.h>
#include <time.h>

char* getCurrentDate(){
	printf("\nIn getCurrentDate");

	char buffer[80];
	time_t rawTime;
	struct tm * timeinfo;
	time (&rawTime);
	timeinfo = localtime(&rawTime);
	strftime(buffer, 80, "%d_%m_%Y", timeinfo);

	printf("\nTime: %s", buffer);

	return buffer;
}
