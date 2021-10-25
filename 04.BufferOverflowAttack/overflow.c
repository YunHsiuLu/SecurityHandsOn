#include <stdio.h>
#include <stdint.h>

int main() {
	int8_t array[10] = {0};

	for (int i = 0; i < 5; i++) {
		scanf("%d", &(array[4-i]));
	}
	for (int i = 0; i < 5; i++) {
		printf("%d ", array[i]);
	}
	return 0;
}
