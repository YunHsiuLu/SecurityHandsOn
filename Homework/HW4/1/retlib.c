#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#ifndef BUF_SIZE
#define BUF_SIZE 12
#endif

int bof(char *str) {
	char buffer[BUF_SIZE];
	unsigned int *framep;

	// Copy ebp into framep
	asm("movl %%ebp, %0" : "=r" (framep));

	/* print out information for experiment purpose */
	printf("Address of buffer[] inside bof(): 0x%.8x\n", (unsigned)buffer);
	printf("Frame Pointer value inside bof(): 0x%.8x\n", (unsigned)framep);

	strcpy(buffer, str); // buffer overflow!

	return 1;
}

int main(int argc, char **argv){
	char input[1000];
	FILE *badfile;

	badfile = fopen("badfile", "r");
	int length = fread(input, sizeof(char), 1000, badfile);
	printf("Address of input[] inside main(): 0x%x\n", (unsigned int) input);
	printf("Input size: %d\n", length);
	bof(input);
	
	printf("(^_^)(^_^) Returne Properly (^_^)(^_^)\n");
	return 1;
}

// This function will be used in the optional task
void foo(){
	static int i = 1;
	printf("Function foo() is invoked %d times\n", i++);
	return;
}

