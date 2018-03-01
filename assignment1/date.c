#include <stdio.h>
#include <time.h>

char* getCurrentDate(){

	char buffer[80];
	time_t rawTime;
	struct tm * timeinfo;
	time (&rawTime);
	timeinfo = localtime(&rawTime);
	strftime(buffer, 80, "%d_%m_%Y", timeinfo);

	return buffer;
}
