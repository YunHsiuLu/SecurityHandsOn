#include <stdio.h>
#include <stdlib.h>

void main() {
	char *shell = getenv("MYSHELL");
	if (shell)
		printf("/bin/sh addr: 0x%x\n", (unsigned int) shell);
}
