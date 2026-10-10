#include <stdio.h>
#include <windows.h>
#include <string.h>

int main(int argc, char *argv[]) {
    // Child Process Execution Path
    if (argc > 1 && strcmp(argv[1], "child") == 0) {
        printf("Child executing task...\n");
        Sleep(2000); // sleep(2) in milliseconds (2000ms)
        printf("Child exiting with code 42\n");
        return 42;   // EXIT(42)
    }

    // Parent Process Execution Path
    printf("Parent waiting for child...\n");

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

    // CALL wait(&status) - Blocks parent until child terminates
    WaitForSingleObject(pi.hProcess, INFINITE);

    // EXTRACT_EXIT_CODE(status)
    DWORD exit_code = 0;
    GetExitCodeProcess(pi.hProcess, &exit_code);

    printf("Parent: Child terminated with exit status %lu\n", exit_code);

    // Clean up handles
    CloseHandle(pi.hProcess);
    CloseHandle(pi.hThread);

    return 0;
}