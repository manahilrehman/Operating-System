#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/prctl.h>

int main() {
    // Process A registers as subreaper
    prctl(PR_SET_CHILD_SUBREAPER, 1);

    if (fork() == 0) {
        // Process B
        if (fork() == 0) {
            // Process C
            sleep(1); // Wait for Process B to exit
            printf("Process C adopted by Subreaper PPID: %d\n", getppid());
            exit(0);
        }
        exit(0); // Process B exits immediately, orphaning C
    }

    // Process A reaps both B and adopted descendant C
    wait(NULL);
    wait(NULL);
    return 0;
}