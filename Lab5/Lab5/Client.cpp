#include <windows.h>
#include <iostream>
#include <string>
#include "common.h"
#include "pipe_utils.h"

using namespace std;

const char* PIPE_NAME = R"(\\.\pipe\LibraryPipe)";

void printError(const char* msg) {
    cerr << msg << " Error: " << GetLastError() << endl;
}

int main() {
    cout << "Client starting..." << endl;

    HANDLE hPipe = connectToServerPipe(PIPE_NAME, 5000);

    if (hPipe == INVALID_HANDLE_VALUE) {
        printError("connectToServerPipe failed");
        return 1;
    }

    bool running = true;

    while (running) {
        cout << endl << "Choose operation:" << endl << "1 - Read record"
        << endl << "2 - Modify record" << endl << "3 - Exit" << endl << "> ";

        int choice;
        cin >> choice;

        if (choice == 3) {
            Request r{ OP_EXIT,0 };
            DWORD written;
            WriteFile(hPipe, &r, sizeof(r), &written, NULL);
            running = false;

            break;
        }
        else if (choice == 1) {
            cout << "Enter employee id to read: ";
            int id; 
            cin >> id;

            Request r{ OP_READ,id };
            DWORD written, read;

            if (!WriteFile(hPipe, &r, sizeof(r), &written, NULL)) {
                printError("WriteFile request failed");

                break;
            }

            employee e;

            if (!ReadFile(hPipe, &e, sizeof(e), &read, NULL) or read != sizeof(e)) {
                printError("ReadFile response failed");

                break;
            }

            if (e.num < 0) {
                cout << "Record not found or error (code=" << e.num << ")" << endl;
            }
            else {
                cout << "Received: id=" << e.num << " name=" << e.name << " hours=" << e.hours << endl;
            }

            cout << "Press Enter to release record...";
            cin.ignore();
            cin.get();

            Request rel{ OP_RELEASE,id };
            WriteFile(hPipe, &rel, sizeof(rel), &written, NULL);
        }
        else if (choice == 2) {
            cout << "Enter employee id to modify: ";
            int id;
            cin >> id;

            Request r{ OP_MODIFY,id }; DWORD written, read;

            if (!WriteFile(hPipe, &r, sizeof(r), &written, NULL)) {
                printError("WriteFile request failed");

                break;
            }

            employee e;

            if (!ReadFile(hPipe, &e, sizeof(e), &read, NULL) or read != sizeof(e)) {
                printError("ReadFile response failed");

                break;
            }

            if (e.num < 0) {
                cout << "Record not found or error (code=" << e.num << ")" << endl;

                continue;
            }

            cout << "Current: id=" << e.num << " name=" << e.name << " hours=" << e.hours << endl;

            string newname;
            double newhours;
            cout << "Enter new name: ";
            cin >> newname;
            cout << "Enter new hours: ";
            cin >> newhours;

            employee ne = e;
            memset(ne.name, 0, sizeof(ne.name));
            strncpy_s(ne.name, newname.c_str(), sizeof(ne.name) - 1);
            ne.hours = newhours;
            Request sendMod{ OP_MODIFY,id }; WriteFile(hPipe, &sendMod, sizeof(sendMod), &written, NULL);
            WriteFile(hPipe, &ne, sizeof(ne), &written, NULL);

            employee confirm;

            if (ReadFile(hPipe, &confirm, sizeof(confirm), &read, NULL) and read == sizeof(confirm)) {
                cout << "Server confirmed: id=" << confirm.num << " name=" << confirm.name << " hours=" << confirm.hours << endl;
            }

            cout << "Press Enter to release record...";
            cin.ignore()
            cin.get();

            Request rel{ OP_RELEASE,id };
            WriteFile(hPipe, &rel, sizeof(rel), &written, NULL);
        }
        else {
            cout << "Unknown choice" << endl;
        }
    }

    CloseHandle(hPipe);
    cout << "Client exiting." << endl;
}
