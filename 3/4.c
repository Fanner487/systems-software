#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <math.h>
#include <string.h>

void main(int argc, char **argv){

	char *input[100];
	char buffer[256];
	FILE *fptr;

	fptr = fopen("log.txt", "a+");


	printf("\nEnter name\n");
	scanf("%s", &input);

	printf("\nName is: %s\n", input);

	fprintf(fptr, "%s\n", input);


}