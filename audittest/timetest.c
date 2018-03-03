#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <signal.h>
#include <stdlib.h>
#include <syslog.h>
#include <sys/stat.h>
#include <time.h>

int main(){
	time_t now;

	struct tm newTime;
	double seconds;
	time(&now);


	newTime = *localtime(&now);
	newTime.tm_hour = 17;
	newTime.tm_min = 43;
	newTime.tm_sec = 0;

	while(1){
		sleep(1);
		time(&now);

		seconds = difftime(now, mktime(&newTime));
		// print()
		printf("\n%.f", seconds);

		if(seconds == 0){
			printf("\nTimesup");

			char buffer[1024];

			// newTime.tm_min += 1;
			newTime.tm_mday += 1;

			strftime(buffer, sizeof(buffer), "%d/%m/%Y %H:%M:%S", &newTime);
			printf("\nNew time :  %s", buffer);
		}

	}

}