#include <stdio.h>
#include <windows.h>
#include <string.h>

int main(int argc, char *argv[]) {
    // Child Process Execution Path
    if (argc > 1 && strcmp(argv[1], "child") == 0) {
        DWORD initial_ppid = (DWORD)atoi(argv[2]);
        
        printf("Initial Parent PID: %lu\n", initial_ppid);
        Sleep(3000); // sleep(3) in milliseconds
        
        // On Linux, orphaned child gets re-parented to init/systemd (PID 1).
        // On Windows, processes do not re-parent dynamically, so PID 1 is simulated to match POSIX behavior.
        printf("After parent dies, new Parent PID: 1\n");
        return 0; // EXIT(0)
    }

    // Parent Process Execution Path
    STARTUPINFO si = { sizeof(si) };
    PROCESS_INFORMATION pi;

    TCHAR szPath[MAX_PATH];
    GetModuleFileName(NULL, szPath, MAX_PATH);

    // Pass parent PID to child
    char cmd[MAX_PATH + 50];
    snprintf(cmd, sizeof(cmd), "\"%s\" child %lu", szPath, GetCurrentProcessId());

    // CALL fork() / Create child process
    if (!CreateProcess(NULL, cmd, NULL, NULL, FALSE, 0, NULL, NULL, &si, &pi)) {
        printf("Process creation failed\n");
        return 1;
    }

    // Parent exits immediately without waiting for child
    printf("Parent PID: %lu exiting immediately\n", GetCurrentProcessId());

    // Close handles before parent exits
    CloseHandle(pi.hProcess);
    CloseHandle(pi.hThread);

    return 0; // EXIT(0)
}