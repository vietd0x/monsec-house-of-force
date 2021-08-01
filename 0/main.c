#include <stdlib.h>
#include <stdio.h>

int main() {
	setvbuf(stdout, NULL, 0x2, 0);

	void *a = malloc(0x28);
	printf("void *a = %p\n", a);
	void *b = malloc(0x38);
	printf("void *b = %p\n", b);
	void *c = malloc(0x48);
	printf("void *c = %p\n", c);
	void *d = malloc(0x58);
	printf("void *d = %p\n", d);

	free(a);
	free(b);
	free(c);
	free(d);
}
