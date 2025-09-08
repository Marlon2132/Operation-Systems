#include <iostream>
#include <fstream>

#include "../Employee/Employee.h"

using namespace std;

int main(int arg_count, char* arg_value[]) {
    if (arg_count != 4) {
        cerr << "Example of usage: Reporter.exe <binary_file_name> <report_file_name> <hourly_rate_value>\n";
        return 1;
    }
    
    if (atof(arg_value[3]) <= 0) {
        cerr << "Hourly rate value should be > 0\n";
        return 1;
    }

    const char* kBinfile = arg_value[1];
    const char* kTxtfile = arg_value[2];
    double rate = atof(arg_value[3]);
    ifstream ifs(kBinfile, ios::binary);

    if (!ifs) {
        cerr << "Cannot open binary file: " << kBinfile << "\n";
        return 1;
    }

    ofstream ofs(kTxtfile);

    if (!ofs) {
        cerr << "Cannot open report file: " << kTxtfile << "\n";
        return 1;
    }

    ofs << "Отчёт по файлу «" << kBinfile << "».\n";
    Employee e;

    //double payment;
    while (ifs.read(reinterpret_cast<char*>(&e), sizeof(e))) {
        //payment = e.hours * rate;
        ofs << e.num << " " << e.name << " " << e.hours << " " << e.hours * rate /*payment*/ << "\n";
    }
    
    ifs.close();
    ofs.close();

    return 0;
}
