#include <windows.h>

HANDLE createServerPipe(const char* pipeName);
HANDLE waitForClientConnect(HANDLE hPipe);
HANDLE connectToServerPipe(const char* pipeName, DWORD timeoutMs = 5000);