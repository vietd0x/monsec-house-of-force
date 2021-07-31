#include <stdlib.h>

int main() {
	void *a = malloc(0x28);
	void *b = malloc(0x38);
	void *c = malloc(0x48);
	void *d = malloc(0x58);

	free(a);
	free(b);
	free(c);
	free(d);
}
