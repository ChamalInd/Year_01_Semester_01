#include <stdio.h>
#include <string.h>

int main() {
	char input[100];
	char *start, *end;
	int len;

	printf("Enter a text: ");
	scanf("%s", input);

	len = strlen(input);
	start = &input[0];
	end = start + len - 1;
	
	for (int i = 0; i < len / 2; i++) {
		if (*start != *end) {
			printf("Not a palindrome\n");
			return 0;
		}
		start++;
		end--;
	}
	printf("Is a palindrome\n");
}
