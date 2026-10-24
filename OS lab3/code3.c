#include <stdio.h>
#include <windows.h>
#include <string.h>

int main(int argc, char *argv[]) {
    // Child Process Execution Path
    if (argc > 1 && strcmp(argv[1], "child") == 0) {
        printf("Child PID: %lu terminating now\n", GetCurrentProcessId());
        return 0; // EXIT(0)
    }

    // Parent Process Execution Path
    STARTUPINFO si = { sizeof(si) };
    PROCESS_INFORMATION pi;

    TCHAR szPath[MAX_PATH];
    GetModuleFileName(NULL, szPath, MAX_PATH);

    char cmd[MAX_PATH + 10];
    snprintf(cmd, sizeof(cmd), "\"%s\" child", szPath);

    // CALL fork() / Create child process
    if (!CreateProcess(NULL, cmd, NULL, NULL, FALSE, 0, NULL, NULL, &si, &pi)) {
        printf("Process creation failed\n");
        return 1;
    }

    // Parent sleeps for 10s without wait() - Simulates Zombie state on Linux
    printf("Parent sleeping for 10s without wait(). Inspect via 'ps -l'\n");
    Sleep(10000); // sleep(10) in milliseconds

    // CALL wait(NULL) - Parent cleans up child handle
    WaitForSingleObject(pi.hProcess, INFINITE);
    printf("Parent cleaned up child. Exiting.\n");

    // Clean up handles
    CloseHandle(pi.hProcess);
    CloseHandle(pi.hThread);

    return 0;
}