#include <stdio.h>

int main() {
	int num = 999, len = 0, n;	
	len = (num <= 9) ? 1 : (num <= 99) ? 2 : (num <= 999) ? 3 : 0 ;

	switch (len) {
		case 3: 
			n = num;
			switch (n) {
				case 100 ... 199 : 
					printf("One Hundred "); 
					n = num % 100; 
					goto twodigit; 
					break;
				case 200 ... 299 : 
					printf("Two Hundred "); 
					n = num % 100; 
					goto twodigit; 
					break;
				case 300 ... 399 : 
					printf("Three Hundred "); 
					n = num % 100; 
					goto twodigit; 
					break;
				case 400 ... 499 : 
					printf("Four Hundred "); 
					n = num % 100; 
					goto twodigit; 
					break;
				case 500 ... 599 : 
					printf("Five Hundred "); 
					n = num % 100; 
					goto twodigit; 
					break;
				case 600 ... 699 : 
					printf("Six Hundred "); 
					n = num % 100; 
					goto twodigit; 
					break;
				case 700 ... 799 : 
					printf("Seven Hundred "); 
					n = num % 100; 
					goto twodigit; 
					break;
				case 800 ... 899 : 
					printf("Eight Hundred "); 
					n = num % 100; 
					goto twodigit; 
					break;
				case 900 ... 999 : 
					printf("Nine Hundred "); 
					n = num % 100; 
					goto twodigit; 
					break;
			}
		case 2:
			n = num;
twodigit:
			switch (n) {
				case 10 : printf("Ten\n"); break;
				case 11 : printf("Eleven\n"); break;
				case 12 : printf("Twelve\n"); break;
				case 13 : printf("Thirteen\n"); break;
				case 14 : printf("Fourteen\n"); break;
				case 15 : printf("Fifteen\n"); break;
				case 16 : printf("Sixteen\n"); break;
				case 17 : printf("Seventeen\n"); break;
				case 18 : printf("Eighteen\n"); break;
				case 19 : printf("Nineteen\n"); break;
				case 20 ... 29 : 
					printf("Twenty "); 
					n = num % 10; 
					goto onedigit; 
					break;
				case 30 ... 39 : 
					printf("Thirty "); 
					n = num % 10; 
					goto onedigit; 
					break;
				case 40 ... 49 : 
					printf("Fourty "); 
					n = num % 10; 
					goto onedigit; 
					break;
				case 50 ... 59 : 
					printf("Fifty "); 
					n = num % 10; 
					goto onedigit; 
					break;
				case 60 ... 69 : 
					printf("Sixty "); 
					n = num % 10; 
					goto onedigit; 
					break;
				case 70 ... 79 : 
					printf("Seventy "); 
					n = num % 10; 
					goto onedigit; 
					break;
				case 80 ... 89 : 
					printf("Eighty "); 
					n = num % 10; 
					goto onedigit; 
					break;
				case 90 ... 99 : 
					printf("Ninety "); 
					n = num % 10; 
					 goto onedigit;
					  break;
			}
		case 1:
			n = num;
onedigit:
			switch (n) {
				case 0 :
					switch (len) {
						case 1:	printf("Zero\n"); break;
					}
				case 1 : printf("One\n"); break;
				case 2 : printf("Two\n"); break;
				case 3 : printf("Three\n"); break;
				case 4 : printf("Four\n"); break;
				case 5 : printf("Five\n"); break;
				case 6 : printf("Six\n"); break;
				case 7 : printf("Seven\n"); break;
				case 8 : printf("Eight\n"); break;
				case 9 : printf("Nine\n"); break;
			}
	}		

	return 0;
}
