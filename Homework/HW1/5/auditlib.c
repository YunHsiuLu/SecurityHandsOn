// auditlib.so
#include <stdio.h>

__attribute__((constructor))

static void init(void){
    printf("I'm loaded from LD_AUDIT\n");
}

unsigned int la_version(unsigned int version){
    return version;
}
