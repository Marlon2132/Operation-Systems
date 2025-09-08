#include <windows.h>
#include <iostream>
#include <fstream>
#include <string>

#include "../Employee/Employee.h"

using namespace std;

// RunProcess
// Starts an ANSI process using the kCmdLine command line and waits for it to complete.
// Returns true if the process is created and completed successfully.
bool RunProcess(const string& kCmdLine) {
    STARTUPINFOA si;
    PROCESS_INFORMATION pi;
    ZeroMemory(&si, sizeof(STARTUPINFO));
    si.cb = sizeof(si);

    if (!CreateProcessA(
        NULL,
        const_cast<LPSTR>(kCmdLine.c_str()),
        NULL,
        NULL,
        FALSE,
        0,
        NULL,
        NULL,
        &si,
        &pi))
    {
        cerr << "Error: failed to launch ["
            << kCmdLine
            << "], code="
            << GetLastError()
            << "\n";

        return false;
    }

    WaitForSingleObject(pi.hProcess, INFINITE);
    CloseHandle(pi.hProcess);
    CloseHandle(pi.hThread);

    return true;
}

// ShowBinaryFile
// Shows binary file kBinFile in console
void ShowBinaryFile(const string& kBinFile) {
    ifstream ifs(kBinFile, ios::binary);

    if (!ifs) {
        cerr << "Cannot open binary file: " << kBinFile << "\n";
        return;
    }

    cout << "\n--- Binary file [" << kBinFile << "] ---\n";
    Employee e;

    while (ifs.read(reinterpret_cast<char*>(&e), sizeof(e))) {
        cout << e.num << " " << e.name << " " << e.hours << "\n";
    }

    cout << "--- End of binary file ---\n\n";
    ifs.close();
}

// ShowTextFile
// Shows text file kTxtFile in console
void ShowTextFile(const string& kTxtFile) {
    ifstream ifs(kTxtFile);

    if (!ifs) {
        cerr << "Cannot open report file: " << kTxtFile << "\n";
        return;
    }

    cout << "\n--- Text report [" << kTxtFile << "] ---\n";
    string line;

    while (getline(ifs, line)) {
        cout << line << "\n";
    }

    cout << "--- End of report ---\n\n";
    ifs.close();
}

int main() {
    setlocale(LC_ALL, "Russian");

    cout << "Enter binary filename and record count: ";
    string kBinFile;
    int count;

    if (!(cin >> kBinFile >> count)) {
        cerr << "Input error\n";
        return 1;
    }
    /*else if (count <= 0) {
        cerr << "Invalid record count. It should be > 0\n";
        return 1;
    }*/

    string creatorCmd = "Creator.exe " + kBinFile + " " + to_string(count);

    if (!RunProcess(creatorCmd)) {
        return 1;
    }

    ShowBinaryFile(kBinFile);

    cout << "Enter report filename and hourly rate: ";
    string reportFile;
    double rate;

    if (!(cin >> reportFile >> rate)) {
        cerr << "Input error\n";
        return 1;
    }
    /*else if (rate <= 0.0) {
        cerr << "Invalid hourly rate. It should be > 0\n";
        return 1;
    }*/

    string reporterCmd = "Reporter.exe " + kBinFile + " " + reportFile + " " + to_string(rate);

    if (!RunProcess(reporterCmd)) {
        return 1;
    }

    ShowTextFile(reportFile);

    cout << "All done.\n";

    return 0;
}
