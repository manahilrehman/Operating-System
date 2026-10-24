#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main() {
    pid_t p2 = fork();
    if (p2 < 0) {
        perror("Fork failed");
        exit(1);
    }
    if (p2 == 0) {
        // Child 1 context
        pid_t p3 = fork();
        if (p3 < 0) {
            perror("Fork failed");
            exit(1);
        }
        if (p3 == 0) {
            // Grandchild context
            printf("[Grandchild] PID: %d | Parent: %d\n", getpid(), getppid());
            exit(0);
        }
        wait(NULL); // Child 1 waits for Grandchild
        printf("[Child 1] PID: %d | Parent: %d\n", getpid(), getppid());
        exit(0);
    }
    wait(NULL); // Parent waits for Child 1
    printf("[Parent] All descendents have completed.\n");
    return 0;
}