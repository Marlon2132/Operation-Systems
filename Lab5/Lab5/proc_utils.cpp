#include <sstream>
#include <iostream>
#include "proc_utils.h"

std::vector<PROCESS_INFORMATION> launchClients(int count, const std::string& clientExeName) {
    std::vector<PROCESS_INFORMATION> procs;
    procs.reserve(count);

    for (int i = 0; i < count; ++i) {
        STARTUPINFOA si;
        PROCESS_INFORMATION pi;
        ZeroMemory(&si, sizeof(si));
        si.cb = sizeof(si);
        ZeroMemory(&pi, sizeof(pi));

        std::ostringstream cmd;
        cmd << "\"" << clientExeName << "\" " << i + 1;

        std::string cmdStr = cmd.str();
        char* cmdLine = _strdup(cmdStr.c_str());

        BOOL ok = CreateProcessA(
            NULL,           // lpApplicationName
            cmdLine,        // lpCommandLine
            NULL,           // lpProcessAttributes
            NULL,           // lpThreadAttributes
            FALSE,          // bInheritHandles
            0,              // dwCreationFlags
            NULL,           // lpEnvironment
            NULL,           // lpCurrentDirectory (NULL = current)
            &si,
            &pi
        );

        free(cmdLine);

        if (!ok) {
            std::cerr << "CreateProcess failed for client " << i + 1 << ", Error: " << GetLastError() << "\n";

            continue;
        }

        procs.push_back(pi);
        std::cout << "Launched client " << i + 1 << " (PID=" << pi.dwProcessId << ")\n";
    }

    return procs;
}

void waitForClientsAndClose(std::vector<PROCESS_INFORMATION>& procs) {
    if (procs.empty()) {
        return;
    }

    std::vector<HANDLE> handles;
    handles.reserve(procs.size());
    for (auto& pi : procs) {
        handles.push_back(pi.hProcess);
    }

    const DWORD MAX_WAIT = MAXIMUM_WAIT_OBJECTS;
    size_t idx = 0;

    while (idx < handles.size()) {
        size_t batch = std::min<size_t>(MAX_WAIT, handles.size() - idx);
        DWORD res = WaitForMultipleObjects((DWORD)batch, &handles[idx], TRUE, INFINITE);

        if (res == WAIT_FAILED) {
            std::cerr << "WaitForMultipleObjects failed: " << GetLastError() << "\n";

            break;
        }

        idx += batch;
    }

    for (auto& pi : procs) {
        CloseHandle(pi.hProcess);
        CloseHandle(pi.hThread);
    }

    procs.clear();
}
