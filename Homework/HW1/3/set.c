#include <stdio.h>
#include <unistd.h>

int main() {
    printf("Real user id: %d, Effective user id: %d\n", getuid(), geteuid());
    //setuid(1200);
    seteuid(1200);
    printf("Real user id: %d, Effective user id: %d\n", getuid(), geteuid());
    //setuid(1000);
    seteuid(1000);
    printf("Real user id: %d, Effective user id: %d\n", getuid(), geteuid());
    return 0;    
}
