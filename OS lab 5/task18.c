#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/wait.h>

int main() {
    int fd = open("log.txt", O_CREAT | O_RDWR | O_TRUNC, 0644);
    if (fd < 0) {
        perror("open failed");
        exit(1);
    }

    pid_t pid = fork();
    if (pid < 0) {
        perror("fork failed");
        exit(1);
    }
    if (pid == 0) {
        write(fd, "Child Data\n", 11);
        close(fd);
        exit(0);
    } else {
        wait(NULL);
        write(fd, "Parent Data\n", 12);
        close(fd);
    }
    printf("Both lines appear in log.txt without file offset collision\n");
    return 0;
}