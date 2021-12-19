#include <string.h>
struct S { struct T { char buf[5]; int x; }t; char buf[20]; }var;
int main(void) {
	strcpy(&var.t.buf[1], "abcdefg");
	return 0;
}
