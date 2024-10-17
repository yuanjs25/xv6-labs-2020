#include "kernel/types.h"
#include "kernel/param.h"
#include "user/user.h"

int read_line(char *buf, int max) {
    int i = 0;
    char c;

    while (i < max - 1) {
        if (read(0, &c, 1) == 1) {
            if (c == '\n') {
                buf[i] = '\0'; 
                return i;
            }
            buf[i++] = c;
        } else {
            break;
        }
    }
    buf[i] = '\0'; 
    return i;
}

int main(int argc, char *argv[]) {
    if (argc < 2) {
        fprintf(2, "Usage: xargs <command>\n");
        exit(1);
    }

    char buf[512];
    char *new_argv[MAXARG]; 
    int n;

    for (n = 0; n < argc - 1; n++) {
        new_argv[n] = argv[n + 1]; 
    }

    while (read_line(buf, sizeof(buf)) > 0) {
        new_argv[n] = buf; 
        new_argv[n + 1] = 0; 

        if (fork() == 0) {
            exec(new_argv[0], new_argv);
            fprintf(2, "exec %s failed\n", new_argv[0]);
            exit(1);
        } else {
            wait(0);
        }
    }

    exit(0);
}
