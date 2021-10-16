#include <unistd.h>
#include <stdio.h>

extern char **environ;
int main() {
    char cmd[] = "/bin/sh";
    char *argv[] = {"ls", NULL};
    char *envp[] = {NULL};
    
    printf("Start of execve call %s:\n", cmd);
    printf("==========================================\n");
    

    execve(cmd , argv, envp);
    //printf("Debug here!\n");

    return 0;
}
