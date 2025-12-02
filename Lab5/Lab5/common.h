#include <windows.h>

struct employee {
    int num;
    char name[10];
    double hours;
};

enum OpCode {
    OP_READ = 1,
    OP_MODIFY = 2,
    OP_RELEASE = 3,
    OP_EXIT = 4
};

struct Request {
    int op;
    int id;
};
