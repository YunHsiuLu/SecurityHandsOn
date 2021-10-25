#include <string.h>

void foo( char *str ) {
    char buffer[8];
    strcpy( buffer, str );
}

int main() {
    char *str = "I am longer than 8.";
    foo ( str );
    return 0;
}
