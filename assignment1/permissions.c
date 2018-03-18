/*
Changes the permissions of /var/www/ between 777 and 744
chmod() in C doesn't allow recursive chmodding (-R) flag. Need to do it manually
*/
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <unistd.h>

#include "messagequeue.h"

void lockSite(){

    char *directory = "/home/eamon/Documents/software/systems-software/assignment1/var/www/html/intranet/";

    pid_t cpid, w;
    int status;

    cpid = fork();
    if (cpid == -1) {
        perror("fork");
        exit(EXIT_FAILURE);
    }

    if (cpid == 0) {    

        // Command execution in here
        
        printf("Child PID is %ld\n", (long) getpid());
        
        execlp("chmod", "chmod", "-R", "555", directory, NULL);

    } 
    else { 
        /* Code executed by parent */
        do {

            // Waits for the child process to exit and return its status code and sends
            // an appropriate info/error message back to the daemon to log
            
            w = waitpid(cpid, &status, WUNTRACED | WCONTINUED);
            
            if (w == -1) {
                perror("waitpid");
                exit(EXIT_FAILURE);
            }

            if (WIFEXITED(status)) {
                
                printf("exited, status=%d\n", WEXITSTATUS(status));
            }

            if(status == 0){
                printf("Exited correctly\n");
                sendQueueMessage("INFO: Locked site");
            }
            else{
                sendQueueMessage("ERROR: LOCKFILES");
            }
        } while (!WIFEXITED(status) && !WIFSIGNALED(status));
    }
}

void unlockSite(){

    char *directory = "/home/eamon/Documents/software/systems-software/assignment1/var/www/html/intranet/";

    pid_t cpid, w;
    int status;

    cpid = fork();
    if (cpid == -1) {
        perror("fork");
        exit(EXIT_FAILURE);
    }

    if (cpid == 0) {            /* Code executed by child */
        printf("Child PID is %ld\n", (long) getpid());
        
        execlp("chmod", "chmod", "-R", "777", directory, NULL);

    } 
    else { 
        /* Code executed by parent */
        do {

            w = waitpid(cpid, &status, WUNTRACED | WCONTINUED);
            if (w == -1) {
                perror("waitpid");
                exit(EXIT_FAILURE);
            }

            if (WIFEXITED(status)) {
                
                printf("exited, status=%d\n", WEXITSTATUS(status));
            }

            if(status == 0){
                printf("Exited correctly\n");
                sendQueueMessage("INFO: Unlocked site");
            }
            else{
                sendQueueMessage("ERROR: UNLOCK FILES");
            }
        } while (!WIFEXITED(status) && !WIFSIGNALED(status));
    }
}

void setFolderPermissions(){

    char *directoryLive = "/home/eamon/Documents/software/systems-software/assignment1/var/www/html/live/";
    char *directoryBackup = "/home/eamon/Documents/software/systems-software/assignment1/var/www/html/backup/";

    pid_t cpid, w;
    int status;

    cpid = fork();
    if (cpid == -1) {
        perror("fork");
        exit(EXIT_FAILURE);
    }

    if (cpid == 0) {            /* Code executed by child */
        printf("Child PID is %ld\n", (long) getpid());
        
        execlp("chmod", "chmod", "-R", "555", directoryLive, directoryBackup ,NULL);

    } 
    else { 
        /* Code executed by parent */
        do {

            w = waitpid(cpid, &status, WUNTRACED | WCONTINUED);
            if (w == -1) {
                perror("waitpid");
                exit(EXIT_FAILURE);
            }

            if (WIFEXITED(status)) {
                
                printf("exited, status=%d\n", WEXITSTATUS(status));
            } 
            else if (WIFSIGNALED(status)) {
                
                printf("killed by signal %d\n", WTERMSIG(status));
            } else if (WIFSTOPPED(status)) {
                
                printf("stopped by signal %d\n", WSTOPSIG(status));
            } else if (WIFCONTINUED(status)) {

                printf("continued\n");
            }

            if(status == 0){
                printf("Exited correctly\n");
                sendQueueMessage("INFO: Set backup and live permissions");
            }
            else{
                sendQueueMessage("ERROR: BACKUP AND LIVE PERMISSIONS");
            }
        } while (!WIFEXITED(status) && !WIFSIGNALED(status));
    }
}