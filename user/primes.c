#include "kernel/types.h"
#include "user/user.h"

void mapping(int n, int pd[]) {
    close(n);              
    dup(pd[n]);            
    close(pd[0]);          
    close(pd[1]);          
}

void primes() {
    int prime, num;
    int fd[2];

    if (read(0, &prime, sizeof(prime)) == 0) {
        close(0); 
        exit(0);
    }

    printf("prime %d\n", prime);

    pipe(fd);

    if (fork() == 0) {
        mapping(1, fd);

        while (read(0, &num, sizeof(num)) != 0) {
            if (num % prime != 0) {
                write(1, &num, sizeof(num));
            }
        }
    } else {
        wait(0);
        mapping(0, fd);
        primes();
    }
}

int main(int argc, char *argv[]) {
    int fd[2];
    pipe(fd);

    if (fork() == 0) {
        mapping(1, fd);

        for (int i = 2; i <= 35; i++) {
            write(1, &i, sizeof(i));
        }
    } else {
        wait(0);
        mapping(0, fd);
        primes();
    }

    exit(0);
}
