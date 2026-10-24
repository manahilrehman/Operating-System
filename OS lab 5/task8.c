#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdbool.h>

int main() {
    pid_t pid = fork();
    if (pid < 0) {
        perror("Fork failed");
        exit(1);
    }
    if (pid == 0) { 
        sleep(3); 
        exit(0); 
    } else {
        int status;
        while (true) {
            pid_t result = waitpid(pid, &status, WNOHANG);
            if (result == 0) {
                printf("Parent computing independent background tasks...\n");
                usleep(500000);
            } else if (result == pid) {
                printf("Child finished! Parent wrapping up.\n");
                break;
            }
        }
    }
    return 0;
}