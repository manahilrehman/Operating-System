#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <signal.h>

int main() {
    struct sigaction sa;
    sa.sa_handler = SIG_IGN;
    sigemptyset(&sa.sa_mask);
    sa.sa_flags = SA_NOCLDWAIT;
    sigaction(SIGCHLD, &sa, NULL);

    if (fork() == 0) {
        printf("Child terminating immediately.\n");
        exit(0);
    }

    // Parent sleeps; kernel deallocates child PCB automatically
    sleep(10);
    return 0;
}