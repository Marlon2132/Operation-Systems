#include <iostream>
#include <string>
#include <windows.h>

using namespace std;

int main(int argc, char** argv) {
    if (argc < 3) {
        cout << "Too few arguments passed!" << endl;

        return -1;
    }

    string file_name = argv[1];
    unsigned short sender_num = static_cast<unsigned short>(atoi(argv[2]));

    HANDLE process_start_event = OpenEventA(EVENT_MODIFY_STATE | SYNCHRONIZE, FALSE, (string("SENDER_") + argv[2] + "_STARTED").c_str());

    if (process_start_event == NULL) {
        cout << "Failed to open start event!" << endl;

        return -1;
    }

    SetEvent(process_start_event);

    string temp_string;
    cout << "Enter 0 to exit, otherwise enter a number of messages to send: ";
    cin >> temp_string;
}
