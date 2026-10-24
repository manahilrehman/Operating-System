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
        printf("Child exiting immediately (PID: %d)\n", getpid());
        exit(0); // Becomes zombie because parent does not reap it
    } else {
        printf("Parent sleeping 20s. Run: ps -el | grep %d\n", pid);
        sleep(20);
        wait(NULL); // Zombie is finally reaped and deallocated here
        printf("Zombie process reaped.\n");
    }
    return 0;
}