#include <windows.h>
#include <iostream>
#include <vector>
#include <thread>
#include <conio.h>
#include "common.h"
#include "file_utils.h"
#include "lock_utils.h"
#include "pipe_utils.h"

using namespace std;

const char* PIPE_NAME = R"(\\.\pipe\LibraryPipe)";
const char* DATA_FILE = "employees.dat";

int main() {
    cout << "Server starting..." << endl;

    int n;
    cout << "Enter number of employees to create: ";
    cin >> n;

    vector<employee> v;

    for (int i = 0; i < n; ++i) {
        employee e;
        cout << "Employee #" << i + 1 << " id: ";
        cin >> e.num;

        string name;
        cout << "name: ";
        cin >> name;

        memset(e.name, 0, sizeof(e.name));
        strncpy_s(e.name, name.c_str(), sizeof(e.name) - 1);
        cout << "hours: ";
        cin >> e.hours;
        v.push_back(e);
    }

    if (!writeEmployeesToFile(DATA_FILE, v)) {
        return 1;
    }

    printFileContents(DATA_FILE);
}
