#include "utils/input_parsing.h"

#include <iostream>
#include <string>
#include <windows.h>

using namespace std;

int main(int argc, char** argv) {
    string file_name;
    cout << "Enter the binary file name:" << endl;
    cin >> file_name;

    while (!CheckFileName(file_name, "", false)) {
        cout << "Enter the binary file name:" << endl;
        cin >> file_name;
    }

    string temp_string;
    cout << "Enter the number of message entries in the binary file:" << endl;
    cin >> temp_string;

    while (!CheckIfPositiveLong(temp_string, false)) {
        cout << "Enter the number of message entries in the binary file:" << endl;
        cin >> temp_string;
    }

    long number_of_entries;
    number_of_entries = stol(temp_string);
}
