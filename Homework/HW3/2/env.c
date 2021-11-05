#include <stdio.h>
#include <stdlib.h>

int main(int argc, char **argv, char** env) {
    char c = 0;
    printf("Stack address: %p\n", &c);

    while (*env)
        printf("%s\n", *env++);

	return 0;
}
