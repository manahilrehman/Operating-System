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
        printf("Child started. Initial Parent PID: %d\n", getppid());
        sleep(2); // Wait for original parent to exit
        printf("Child after parent exit. New Parent PID: %d\n", getppid());
        exit(0);
    } else {
        printf("Parent exiting immediately. Child is now orphaned.\n");
        exit(0);
    }
    return 0;
}