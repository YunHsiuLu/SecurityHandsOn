#include <stdio.h>

extern char **environ;
int main(int argc, char *argv[], char *envp[]) {
    int i = 0;
    
    while (environ[i] != NULL) {
        printf("%s\n", environ[i++]);
    }
    return 0;
}
