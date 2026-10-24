#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <string.h>

#define MAX_LINE 80

int main() {
    char *args[MAX_LINE/2 + 1];
    int should_run = 1;

    while (should_run) {
        printf("osh> ");
        fflush(stdout);

        char input[MAX_LINE];
        if (fgets(input, MAX_LINE, stdin) == NULL) break;
        
        input[strcspn(input, "\n")] = 0;
        if (strlen(input) == 0) continue;
        if (strcmp(input, "exit") == 0) break;

        int i = 0;
        char *token = strtok(input, " ");
        while (token != NULL && i < MAX_LINE/2) {
            args[i++] = token;
            token = strtok(NULL, " ");
        }
        args[i] = NULL;

        pid_t pid = fork();
        if (pid < 0) {
            perror("Fork failed");
            exit(1);
        } else if (pid == 0) {
            execvp(args[0], args);
            perror("Command execution failed");
            exit(1);
        } else {
            wait(NULL);
        }
    }
    return 0;
}