#include <stdlib.h>
#include <stdio.h>
#include <string.h>

int foo(char *str) {
	char buffer[100];
	printf("%p\n", buffer);
	strcpy(buffer, str);
	return 1;
}

int main() {
	char str[300];
	FILE *badfile = NULL;

	// badfile here is a malicious input.
	badfile = fopen("badfile", "r");
	fread(str, sizeof(char), 300, badfile);
	foo(str);

	printf("Return properly.\n");
	return 0;
}
