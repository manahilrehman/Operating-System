#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main() {
    pid_t c1 = fork();
    if (c1 < 0) {
        perror("Fork failed");
        exit(1);
    }
    if (c1 == 0) {
        printf("First Sibling running with PID: %d\n", getpid());
        exit(0);
    }

    // Guaranteed only parent runs here
    pid_t c2 = fork();
    if (c2 < 0) {
        perror("Fork failed");
        exit(1);
    }
    if (c2 == 0) {
        printf("Second Sibling running with PID: %d\n", getpid());
        exit(0);
    }

    // Parent reaps both siblings
    wait(NULL);
    wait(NULL);

    return 0;
}