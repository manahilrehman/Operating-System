#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <signal.h>

void sigchld_handler(int sig) {
    int status;
    // Drain all terminated children to avoid queue coalescing issues
    while (waitpid(-1, &status, WNOHANG) > 0) {
        printf("Asynchronously reaped a terminated child.\n");
    }
}

int main() {
    signal(SIGCHLD, sigchld_handler);
    for (int i = 1; i <= 5; i++) {
        if (fork() == 0) {
            sleep(rand() % 3 + 1);
            exit(0);
        }
    }
    // Parent continues primary processing without blocking
    while (1) { 
        sleep(1); 
    }
    return 0;
}