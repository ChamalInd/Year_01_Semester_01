#include <stdio.h>

#define IN  1
#define OUT 0

int main() {
	int c;
	int nw, nc, nl, state;
	
	nw = nc = nl = 0;
	state = OUT;

	while ((c = getchar()) != EOF) {
		++nc;
		if (c == '\n') {
			++nl;
		} else if (c == ' ' || c == '\t' || c == '\n') {
			state = OUT;
		} else if (state == OUT) {
			++nw;
			state = IN;
		}
	}
	printf("Word Count: %8d\nLine Count: %8d\nCharacter Count: %3d\n", nw, nl, nc);
	return 0;
}
