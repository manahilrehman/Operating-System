#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main() {
    pid_t pid = fork();

    if (pid < 0) {
        perror("Fork failed");
        exit(1);
    } else if (pid == 0) {
        // Child process context
        printf("Child Process -> PID: %d | Parent PID: %d\n", getpid(), getppid());
        exit(0);
    } else {
        // Parent process context
        printf("Parent Process -> PID: %d | Child PID: %d\n", getpid(), pid);
        wait(NULL); // Wait for child completion
    }
    return 0;
}