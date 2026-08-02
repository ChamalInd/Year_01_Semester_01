#include <stdio.h>

int main() {
	int c;
	int tab_count, newline_count, blank_count;
	
	tab_count = 0;
	newline_count = 0;
	blank_count = 0;

	while ((c = getchar()) != EOF) {
		if (c == '\n') {
			++newline_count;
		} else if (c == '\t') {
			++tab_count;
		} else if (c == ' ') {
			++blank_count;
		}
	}
	printf("Newlines: %d\nTabs: %d\nBlanks: %d\n", newline_count, tab_count, blank_count);
	return 0;
}
