#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <math.h>
#include <string.h>

#include "date.h"


void syncFiles(){

	char *source = "/home/eamon/Documents/software/systems-software/assignment1/var/www/html/intranet/";
	char *destination = "/home/eamon/Documents/software/systems-software/assignment1/var/www/html/live/";
	char *command = "rsync -r /home/eamon/Documents/software/systems-software/assignment1/var/www/html/intranet/ /home/eamon/Documents/software/systems-software/assignment1/var/www/html/live/";

	execlp("rsync", "rsync", "-r", source, destination, NULL);

	// system(command);



}


// //Update the website fron the intranet site
// #include <stdio.h>
// #include <stdlib.h>
// #include <time.h>
// #include <string.h>
// #include <errno.h>
// #include <syslog.h>
// #include <setjmp.h>

// //#include "date.h"
// #include "updatewebsite.h"

// void updateWebsite(){
//   char * update_exec_path = "rsync -r /Users/neilpelows/Documents/SystemsSoftware/assignment1/LIVEWEBSITE /var/www";

//   if (system(update_exec_path) < 0){
//     openlog("systemsoftware_log", LOG_PID|LOG_CONS, LOG_USER);
//     syslog(LOG_INFO, "Failed to update live website: %s", strerror(errno));
//     closelog();
//   }
// }
