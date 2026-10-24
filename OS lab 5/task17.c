#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

void build_tree(int level, int max_depth) {
    if (level >= max_depth) return;

    pid_t left = fork();
    if (left < 0) { perror("fork failed"); exit(1); }
    if (left == 0) {
        printf("Level %d Left Child: PID %d\n", level + 1, getpid());
        build_tree(level + 1, max_depth);
        exit(0);
    }

    pid_t right = fork();
    if (right < 0) { perror("fork failed"); exit(1); }
    if (right == 0) {
        printf("Level %d Right Child: PID %d\n", level + 1, getpid());
        build_tree(level + 1, max_depth);
        exit(0);
    }

    waitpid(left, NULL, 0);
    waitpid(right, NULL, 0);
}

int main() {
    printf("Root Process PID: %d\n", getpid());
    build_tree(0, 3);
    return 0;
}