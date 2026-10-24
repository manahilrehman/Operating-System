#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main() {
    pid_t pidA = fork();
    if (pidA < 0) {
        perror("Fork failed");
        exit(1);
    }
    if (pidA == 0) {
        sleep(4);
        exit(10);
    }

    pid_t pidB = fork();
    if (pidB < 0) {
        perror("Fork failed");
        exit(1);
    }
    if (pidB == 0) {
        sleep(1);
        exit(20);
    }

    int status;
    // Wait specifically for Child A first, even though Child B finishes earlier
    waitpid(pidA, &status, 0);
    if (WIFEXITED(status)) {
        printf("Child A reaped with status: %d\n", WEXITSTATUS(status));
    }

    // Now reap Child B
    waitpid(pidB, &status, 0);
    if (WIFEXITED(status)) {
        printf("Child B reaped with status: %d\n", WEXITSTATUS(status));
    }

    return 0;
}