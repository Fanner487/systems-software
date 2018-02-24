#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

int main( int argc, char *argv[] )  {

	int aor;

	int s1 = atoi(argv[1]);
	int s2 = atoi(argv[2]);

	aor = areaOfRectangle(s1, s2);
	printf("Area of Recctangle: %d", aor);

	
}
