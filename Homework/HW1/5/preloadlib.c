// preloadlib.so
#include <stdio.h>

__attribute__((constructor))

static void init(void){
    printf("I'm loaded from LD_PRELOAD\n");
}
