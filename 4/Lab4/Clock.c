#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>

int main ()
{

	time_t now;
	double seconds;
	struct tm newyear;

	time(&now);
	newyear = *localtime(&now);

	newyear.tm_hour = 14;
	newyear.tm_min = 39;
	newyear.tm_sec = 0;


	while(1){
	time(&now);
	seconds = difftime(now,mktime(&newyear));
	printf("Seconds: %f\n", seconds);
	sleep(1);
	
	if( seconds == 0){
	
	printf("Well done");	
	}	
	}
}
