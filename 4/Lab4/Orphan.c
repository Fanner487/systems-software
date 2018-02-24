//Orphan Example
//The child process is adopted by init process, when parent process dies.
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>

int main()
{
	//Implementation for Singleton pattern if desired(Only one instance running)
	//Create a child process

	int pid = fork();

	if (pid > 0)
	{

	//if PID > 0 :: this is the parent
	//This process performs printf and finishes

	printf("Parent process");
	sleep(10);
	exit(EXIT_SUCCESS);//Kill the parent needed to make orphan
	}

	else if (pid == 0)
	{

	//Step 1: Create the orphan process
	printf("Child process");

	//Step 2: Elevate the orphan process to session leader, to loose controlling TTY
	//This command runs the process in a new session

	if(setsid() < 0) {exit(EXIT_FAILURE);}

	//Step 3: call umask() to set the file mode creation mask to 0
	//This will allow the daemon to read and write files
	//with the permission/access required
	
	umask(0);

	//Step 4:Change the current working dir to root
	//This will eliminate any issues of running on a mounted drive,
	//that potentially could be removed....

	if(chdir("/") < 0) { exit(EXIT_FAILURE); }

	//step 5: close all open files descriptors
	//Close all open files desccriptors

	int x;
	for(x = sysconf(_SC_OPEN_MAX); x>=0; x--)
	{
		close(x);
	}
	
	//Orphan logic goes here!
	//Keep process running with infinite loop
	//When the parent finihes after 10 seconds.
	//the getppid() will return 1 as the parent (init process)
	while(1)
	{
		sleep(1);
		printf("Child: My parent is: %i\n", getppid());
	}
	}

	return(0);
}
