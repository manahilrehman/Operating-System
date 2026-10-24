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
        for (int i = 1; i <= 5; i++) {
            printf("Child working... step %d\n", i);
            usleep(500000);
        }
        exit(0);
    } else {
        printf("Parent waiting for child completion...\n");
        wait(NULL); // Blocks execution until child finishes
        printf("Parent resumed: Child terminated successfully.\n");
    }
    return 0;
}