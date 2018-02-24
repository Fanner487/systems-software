#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "areaOfRectangle.h"
#include "areaOfCircle.h"
#include "areaOfTriangle.h"

void main(int argc, char **argv){

	char *shape = argv[1];

	printf("%s\n", shape);

	
	
	if(strcmp(shape, "rectangle") == 0){
		printf("\nIn rectangle\n");
		areaOfRectangle(atoi(argv[2]), atoi(argv[3]));
		
	}

	if(strcmp("circle", shape) == 0){

		printf("\nIn circle\n");
		areaOfCircle(atoi(argv[2]));
		
	}

	if(strcmp("triangle", shape) == 0){

		printf("\nIn triangle\n");
		areaOfTriangle(atoi(argv[2]), atoi(argv[3]));
		
	}

}
