#include <stdio.h>
#include <unistd.h>
#include <signal.h>

void sig_handler(int sigNum){

	if(sigNum == SIGINT){
		printf("SIGINT called\n");
	}
}

int main(void){

	if(signal(SIGINT, sig_handler) == SIG_ERR){
		printf("Something went wrong\n");
	}

	while(1){
		sleep(1);
	}

	return 0;
}