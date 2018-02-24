#include <stdio.h>
#include <string.h>

void appendString(char *s, char c);
void convertToRomanNumeral(int *number, char *romanNumber);

int main(int argc, char **argv) {
	char romanString[256] = "";
	int number = 0;

	printf("Please enter a number: ");
	scanf("%d", &number);

	convertToRomanNumeral(&number, romanString);

	printf("%s", romanString);

	return 0;
}

void convertToRomanNumeral(int *number, char *romanNumber) {
	int p = 0;
	for(int i=0;i<13;i++) {
		switch(i) {
			case(0): {
				p = 0;
				p = *number/1000;
				for(int j=0;j<p;j++) {
					appendString(romanNumber, 'M');
				}
				*number = *number%1000;	 
				break;
			}

			case(1): {
				p = 0;
				p = *number/900;
				for(int j=0;j<p;j++) {
					appendString(romanNumber, 'C');
					appendString(romanNumber, 'M');
				}
				*number = *number%900;
				break;
			}

			case(2): {
				p = 0;
				p = *number/500;
				for(int j=0;j<p;j++) {
					appendString(romanNumber, 'D');
				}
				*number = *number%500;
				break;
			}

			case(3): {
				p = 0;
				p = *number/400;
				for(int j=0;j<p;j++) {
					appendString(romanNumber, 'C');
					appendString(romanNumber, 'D');
				}
				*number = *number%400;
				break;
			}
			
			case(4): {
				p = 0;
				p = *number/100;
				for(int j=0;j<p;j++) {
					appendString(romanNumber, 'C');
				}
				*number = *number%100;
				break;
			}

			case(5): {
				p = 0;
				p = *number/90;
				for(int j=0;j<p;j++) {
					appendString(romanNumber, 'X');
					appendString(romanNumber, 'C');
				}
				*number = *number%90;
				break;
			}

			case(6): {
				p = 0;
				p = *number/50;
				for(int j=0;j<p;j++) {
					appendString(romanNumber, 'L');
				}
				*number = *number%50;
				break;
			}

			case(7): {
				p = 0;
				p = *number/40;
				for(int j=0;j<p;j++) {
					appendString(romanNumber, 'X');
					appendString(romanNumber, 'L');
				}
				*number = *number%40;
				break;
			}

			case(8): {
				p = 0;
				p = *number/10;
				for(int j=0;j<p;j++) {
					appendString(romanNumber, 'X');
				}
				*number = *number%10;
				break;
			}

			case(9): {
				p = 0;
				p = *number/9;
				for(int j=0;j<p;j++) {
					appendString(romanNumber, 'I');
					appendString(romanNumber, 'X');
				}
				*number = *number%9;
				break;
			}

			case(10): {
				p = 0;
				p = *number/5;
				for(int j=0;j<p;j++) {
					appendString(romanNumber, 'V');
				}
				*number = *number%5;
				break;
			}

			case(11): {
				p = 0;
				p = *number/4;
				for(int j=0;j<p;j++) {
					appendString(romanNumber, 'I');
					appendString(romanNumber, 'V');
				}
				*number = *number%4;
				break;
			}

			case(12): {
				p = 0;
				p = *number/1;
				for(int j=0;j<p;j++) {
					appendString(romanNumber, 'I');
				}
				break;
			}


		}
	}
}

void appendString(char *s, char c) {
	
	int len = strlen(s);
	s[len] = c;
	s[len + 1] = '\0';
}
