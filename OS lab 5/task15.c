#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main() {
    char *args[] = {(char*)"reporter", (char*)"arg1", (char*)"arg2", NULL};
    char *envs[] = {(char*)"LAB_MODULE=OS_PROC", (char*)"SEM=FALL2026", NULL};

    pid_t pid = fork();
    if (pid < 0) {
        perror("Fork failed");
        exit(1);
    }
    if (pid == 0) {
        execve("./reporter", args, envs);
        perror("execve execution failed");
        exit(1);
    }
    wait(NULL);
    return 0;
}