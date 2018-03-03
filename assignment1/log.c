#include <stdio.h>
#include <unistd.h>
#include <syslog.h>
#include <sys/types.h>
#include <fcntl.h>
#include <stdlib.h>
#include <errno.h>
#include <sys/stat.h>


void logInfo(char* log){
	openlog("assignment1", LOG_PID|LOG_CONS, LOG_USER);
	syslog(LOG_INFO, "%s", log);
	closelog();
}

void logError(char* log){
	openlog("assignment1", LOG_PID|LOG_CONS, LOG_USER);
	syslog(LOG_ERR, "%s", log);
	closelog();
}

void logWarning(char* log){
	openlog("assignment1", LOG_PID|LOG_CONS, LOG_USER);
	syslog(LOG_WARNING, "%s", log);
	closelog();
}