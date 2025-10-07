#include <windows.h>
#include <iostream>

using namespace std;

class MarkerControl {
private:
    unsigned int id_;
    HANDLE threadHandle_;
    HANDLE startEvent_;
    HANDLE stopEvent_;

    static DWORD WINAPI ThreadProc(LPVOID param);
    DWORD marker();

public:
    MarkerControl(unsigned int id_);
    unsigned int getId();
    HANDLE getStartEvent();
    HANDLE getStopEvent();
    HANDLE getThreadHandle();
};