#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <signal.h>

int main() {
    if (fork() == 0) {
        exit(0);
    }
    if (fork() == 0) {
        exit(15);
    }
    if (fork() == 0) {
        raise(SIGSEGV);
    }

    int status;
    pid_t reaped_pid;
    while ((reaped_pid = waitpid(-1, &status, 0)) > 0) {
        printf("Harvested PID: %d\n", reaped_pid);
        if (WIFEXITED(status)) {
            printf(" -> Clean termination with exit code: %d\n", WEXITSTATUS(status));
        } else if (WIFSIGNALED(status)) {
            printf(" -> Crashed / killed by signal: %d\n", WTERMSIG(status));
        }
    }
    return 0;
}