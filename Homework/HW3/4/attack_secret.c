#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>

int main() {
	FILE *pFile = fopen("/dev/random", "rb");

	uint32_t guess = 0, secret = 0;

	if (pFile == NULL) {
		perror("Error\n");
		return 0;
	}

	fread(&secret, 4, 1, pFile);
	printf("%u----------->for testing\n", secret);
	while(1) {
		printf("Please enter your guess: ");
		scanf("%u", &guess);

		if (guess == secret)
			break;
		
		printf("Wrong guess! Please guess again.\n");
	}

	printf("Congratulation! The secret is utqewiioa!\n");

	return 0;
}
