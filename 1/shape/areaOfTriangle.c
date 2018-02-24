#include <stdio.h>
#include "areaOfTriangle.h"

int areaOfTriangle(int s1, int s2){

	float side1 = s1;
	float side2 = s2;
	float area;
	
	area = (float)(s1 * s2) / 2;

	printf("Area: %.2f\n", area);
}
