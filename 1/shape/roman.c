

#include<stdio.h>
#include<string.h>
#include<conio.h>

 
int main(){
 
    long int number;
 
    printf("Enter the number you wish to convert to ROMAN Number: ");
    scanf("%d",&number);
 
    char *output = "";

	while(number >= 1000){
		strcat("M", output);

		number -= 1000;
	}

	while(number >= 900){
		strcat("CM", output);

		number -= 900;
	}

	while(number >= 500){
		strcat("D", output);

		number -= 500;
	}

	while(number >= 400){
		strcat("CD", output);

		number -= 400;
	}

	while(number >= 100){
		strcat("C", output);

		number -= 100;
	}


	while(number >= 90){
		strcat("XC", output);

		number -= 90;
	}

	while(number >= 50){
		strcat("L", output);

		number -= 50;
	}

	while(number >= 40){
		strcat("XL", output);

		number -= 40;
	}

	while(number >= 10){
		strcat("X", output);

		number -= 10;
	}


	while(number >= 9){
		strcat("IX", output);

		number -= 9;
	}

	while(number >= 5){
		strcat("V", output);

		number -= 5;
	}


	while(number >= 4){
		strcat("IV", output);

		number -= 4;
	}

	while(number >= 1){
		strcat("I", output);

		number -= 1;
	}

	printf("\n%s\n", output);
	/*
1 - I
4 - IV
5 V
9 IX
10 X
40 XL
50 L
90 XC
100 C
400 CD
500 D
900 CM
1000 M
*/


    return 0;
 
}
