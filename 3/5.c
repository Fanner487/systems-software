#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <math.h>
#include <string.h>


int main(int argc, char **argv){

	int c;

	FILE *file;
	file = fopen("log.txt", "r");

	if(file){
		while((c = getc(file)) != EOF){
			putchar(c);
		}
		fclose(file);
	}

	return 0;
}