#include <stdio.h>
#include <windows.h>
#include <string.h>

int shared_counter = 100; // GLOBAL shared_counter = 100

int main(int argc, char *argv[]) {
    // Child Process Execution Path
    if (argc > 1 && strcmp(argv[1], "child") == 0) {
        shared_counter += 50;
        printf("Child sees shared_counter = %d\n", shared_counter);
        return 0;
    }

    // Parent Process Execution Path
    STARTUPINFO si = { sizeof(si) };
    PROCESS_INFORMATION pi;

    TCHAR szPath[MAX_PATH];
    GetModuleFileName(NULL, szPath, MAX_PATH);

    char cmd[MAX_PATH + 10];
    snprintf(cmd, sizeof(cmd), "\"%s\" child", szPath);

    if (!CreateProcess(NULL, cmd, NULL, NULL, FALSE, 0, NULL, NULL, &si, &pi)) {
        printf("Process creation failed\n");
        return 1;
    }

    // CALL wait(NULL) - Parent waits for child
    WaitForSingleObject(pi.hProcess, INFINITE);

    printf("Parent sees shared_counter = %d\n", shared_counter);

    CloseHandle(pi.hProcess);
    CloseHandle(pi.hThread);

    return 0;
}