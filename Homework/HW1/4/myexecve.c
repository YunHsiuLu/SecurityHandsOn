#include <unistd.h>
#include <stdio.h>

extern char **environ;
int main() {
    char cmd[] = "./userscript.sh";
    char *argv[] = {"userscript", /*"arg1", "arg2", "3",*/ NULL};
    char *envp[] = {NULL};
    
    printf("Start of execve call %s:\n", cmd);
    printf("==========================================\n");
    

    execve(cmd , argv, envp);
    //printf("Debug here!\n");

    return 0;
}
