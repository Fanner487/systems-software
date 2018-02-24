#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>

int main(void){

	time_t now;
	double seconds;
	struct tm newyear;

	time(&now);
	newyear = *localtime(&now);

	newyear.tm_hour = 15;
	newyear.tm_min = 55;
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
