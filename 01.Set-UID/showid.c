#define _GNU_SOURCE
#include <stdio.h>
#include <unistd.h>
#include <pwd.h>

int main() {
	uid_t ruid, euid, suid;
	struct passwd *pwd = NULL;

	getresuid(&ruid, &euid, &suid);

	pwd = getpwuid(ruid);
	printf("Real User ID: %d (%s)\n", ruid, pwd -> pw_name);
	pwd = getpwuid(euid);
	printf("Effective User ID: %d (%s)\n", euid, pwd -> pw_name);
	pwd = getpwuid(suid);
	printf("Saved User ID: %d (%s)\n", suid, pwd -> pw_name);

	return 0;
}
