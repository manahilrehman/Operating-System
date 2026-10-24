#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <signal.h>

int main() {
    pid_t pid = fork();
    if (pid < 0) {
        perror("fork failed");
        exit(1);
    }
    if (pid == 0) {
        while (1) { sleep(1); }
    } else {
        sleep(3);
        int status;
        pid_t check = waitpid(pid, &status, WNOHANG);
        if (check == 0) {
            printf("Child exceeded time limit. Dispatching SIGKILL to PID: %d\n", pid);
            kill(pid, SIGKILL);
            waitpid(pid, &status, 0);
        }
    }
    return 0;
}