#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <syslog.h>
#include <setjmp.h>

#include "log.h"

void setFilePermissions(char mode[]){
  int i;
  int exception_int;

  struct stat st;

  char path[100] = "/home/eamon/Documents/software/systems-software/assignment1/var/www/";

  stat(path, &st);

  i = strtol(mode, 0, 8);

  // chmod(path, i);
  if (chmod(path, i) < 0){

    logError("Unable to change permissions");
  }
  else{
    logInfo("Permissions changed");
  }
}