#include <stdio.h>

void strcpy(char *s, char *t)
{
	while ((*t = *s) != '\0')
	{
		s++;
		t++;
	}
}

int main()
{
	char s[1024], t[1024];
	printf("Enter a string : ");
	scanf("%[^\n]s", s);
	
	strcpy(s, t);
	printf("Copied version : %s\n", t);
}
