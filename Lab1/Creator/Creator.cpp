#include <iostream>
#include <fstream>

#include "../Employee/Employee.h"

using namespace std;

int main(int arg_count, char* arg_value[]) {
    if (arg_count != 3) {
        cerr << "Example of usage: Creator.exe <binary_file_name> <count_of_entries>\n";
        return 1;
    }

    const char* kFilename = arg_value[1];
    int count = atoi(arg_value[2]);

    if (count <= 0) {
        cerr << "Count must be > 0\n";
        return 1;
    }

    ofstream ofs(kFilename, ios::binary);

    if (!ofs) {
        cerr << "Cannot open file for writing: " << kFilename << "\n";
        return 1;
    }

    Employee e;

    for (int i = 0; i < count; i++) {
        cout << "Enter <num> <name> <hours> of Employee #" << (i + 1) << ":\n";
        cin >> e.num >> e.name >> e.hours;

        ofs.write(reinterpret_cast<char*>(&e), sizeof(e));
    }

    ofs.close();

    return 0;
}