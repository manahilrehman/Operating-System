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
    }
    if (pid == 0) {
        printf("Child executing 'ls -la'...\n");
        execlp("ls", "ls", "-la", NULL);
        // Unreachable code if exec succeeds
        perror("execlp failed");
        exit(1);
    } else {
        wait(NULL);
        printf("Parent: Child execution completed.\n");
    }
    return 0;
}