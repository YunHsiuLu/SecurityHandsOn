/*
 * addmsg: log a message with timestamp to a given file
 * call: addmsg file "message"
 */

#include <time.h>
#include <stdio.h>
#include <fcntl.h>
#include <errno.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/stat.h>

int main(int argc, char **argv){
	char *fname;
	FILE *f;
	struct stat buf;
	time_t now;

	if (argc != 3) {
		fprintf(stderr, "Call: addmsg file message\n");
		exit(1);
	}

	/* get time stamp */
	now = time(NULL);

	/* get filename and check we have write access, if it exists */
	fname = argv[1];
	if (stat(fname, &buf)) {
		fprintf(stderr, "addmsg: cannot stat message file\n");
		exit(1);
	} else if (buf.st_uid != getuid()) {
		fprintf(stderr, "addmsg: permission denied\n");
		exit(1);
	}
	
	/* open message file */
	f = fopen(fname, "a");
	if (f == NULL) {
		perror(fname);
		fprintf(stderr, "addmsg: cannot open  message file\n");
		exit(1);
	}

	/* write output */
	fprintf(f, "%s  %s\n", ctime(&now), argv[2]);
	fclose(f);

	return 0;
}
