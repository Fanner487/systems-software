/*
Changes the permissions of /var/www/ between 777 and 744
chmod() in C doesn't allow recursive chmodding (-R) flag. Need to do it manually
*/
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

void lockSite(){

    char *command = "chmod -R 744 /home/eamon/Documents/software/systems-software/assignment1/var/www/html/";

    FILE *fp;
    FILE *outputFile;
    char readbuffer[1024];

    fp = popen(command, "r");
    outputFile = fopen("/home/eamon/Documents/software/systems-software/assignment1/lockfiles.txt", "a+");

    while(fgets(readbuffer, 1024,fp) != NULL){
        fprintf(outputFile, "%s", readbuffer);
    }

    logInfo("Lock site");

    pclose(fp);
}

void unlockSite(){

    char *command = "chmod -R 777 /home/eamon/Documents/software/systems-software/assignment1/var/www/html/";

    FILE *fp;
    FILE *outputFile;
    char readbuffer[1024];

    fp = popen(command, "r");
    outputFile = fopen("/home/eamon/Documents/software/systems-software/assignment1/unlockfiles.txt", "a+");

    while(fgets(readbuffer, 1024,fp) != NULL){
        fprintf(outputFile, "%s", readbuffer);
    }

    logInfo("Unlock site");

    pclose(fp);

}