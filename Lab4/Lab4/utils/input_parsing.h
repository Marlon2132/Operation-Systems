#include <string>
#include <cstddef>
#include <iostream>
#include <stdexcept>
#include <cctype>
#include <climits>

using namespace std;

static const char* kForbiddenFileNameCharacters = "\\/:*?\"<>|";
static const char* kForbiddenFileNames3[] = { "CON", "PRN", "AUX", "NUL" };
static const char* kForbiddenFileNames4[] = { "COM1","COM2","COM3","COM4","COM5","COM6","COM7","COM8","COM9",
                                               "LPT1","LPT2","LPT3","LPT4","LPT5","LPT6","LPT7","LPT8","LPT9" };

bool CheckFileName(string file_name, string required_postfix = "", bool verbose = false);
bool CheckIfPositiveLong(string str, bool verbose = false);