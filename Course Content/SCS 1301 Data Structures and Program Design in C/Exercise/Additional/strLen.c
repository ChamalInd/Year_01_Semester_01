#include <stdio.h>

int strlen(char *s)
{
	int n;
	for (n = 0; *s != '\0'; s++)
		n++;
	return n;
}

int main()
{
	char s[1024];
	printf("Enter a string : ");
	scanf("%[^\n]s", s);
	int len = strlen(s);
	printf("Length of %s : %i\n", s, len);
}
