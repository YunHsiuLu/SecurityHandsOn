#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
	char *pCatStr = "/bin/cat";

	char *pCmd = malloc(strlen(pCatStr) + strlen(argv[1]) + 2);
	sprintf(pCmd, "%s %s", pCatStr, argv[1]);
	system(pCmd);

	return 0;
}
