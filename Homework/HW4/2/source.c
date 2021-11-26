#include <stdio.h>
#include <stdlib.h>

const int global_x = 1;     // stored in data (read-only)
int global_y = 1;           // stored in data (readable / writable)
int global_z;               // stored in bss

int main() {
    const static int x = 1; // stored in data (read-only)
    static int y = 1;       // stored in data (readable / writable)
    static int z;           // stored in bss
    int w = 1;              // stored in stack

    // stored in heap
    char *buf = (char*) malloc(sizeof(char) * 100);
    // print the address
    printf("global_x address: %p (stored in data (read-only))\n", &global_x);
    printf("global_y address: %p (stored in data (readable / writable))\n", &global_y);
    printf("global_z address: %p (stored in bss)\n", &global_z);
    printf("x        address: %p (stored in data (read-only))\n", &x);
    printf("y        address: %p (stored in data (readable / writable))\n", &y);
    printf("z        address: %p (stored in bss)\n", &z);
    printf("w        address: %p (stored in stack)\n", &w);
    printf("buf      address: %p (stored in heap)\n", &buf);
    
    // ...
    free(buf);

    return 0;
}
