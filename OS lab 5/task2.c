#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int counter = 100;

int main() {
    pid_t pid = fork();

    if (pid < 0) {
        perror("Fork failed");
        exit(1);
    } else if (pid == 0) {
        // Modify child copy
        counter += 50;
        printf("[Child] counter = %d at address: %p\n", counter, (void*)&counter);
        exit(0);
    } else {
        sleep(1); // Give child time to modify its variable
        printf("[Parent] counter = %d at address: %p\n", counter, (void*)&counter);
        wait(NULL);
    }
    printf("Addresses appear identical (virtual), but values remain isolated\n");
    return 0;
}