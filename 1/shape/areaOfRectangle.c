#include <stdio.h>
#include "areaOfRectangle.h"

int areaOfRectangle(int s1,int s2){

	int area;
	int side1 = s1;
	int side2 = s2;

	printf("Side 1: %d\n", s1);
	printf("Side 2: %d\n", s2);

	area = side1 * side2;

	printf("Area: %d\n", area);
}
