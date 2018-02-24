#include <stdio.h>
#include "areaOfCircle.h"

int areaOfCircle(int r){

	float pi = 3.14;
	int radius = r;
	
	float area = (3.14 * radius);
	float square = area * area;

	printf("Area: %.2f\n", square);
}
