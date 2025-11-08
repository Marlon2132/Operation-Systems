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
}
