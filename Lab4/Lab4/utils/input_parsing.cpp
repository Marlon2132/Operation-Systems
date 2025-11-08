#include "input_parsing.h"

using namespace std;

bool CheckFileName(string file_name, string required_postfix, bool verbose) {
    if (required_postfix != "") {
        if (file_name.length() < required_postfix.length() or
            file_name.substr(file_name.length() - required_postfix.length(), required_postfix.length()) != required_postfix) {
            if (verbose) {
                cout << "File name must contain " << required_postfix << " postfix!" << endl;
            }

            return false;
        }
    }

    if (file_name.empty()) {
        if (verbose) {
            cout << "File name cannot be empty!" << endl;
        }

        return false;
    }
    else if (file_name.length() > 255) {
        if (verbose) {
            cout << "File name cannot be more than 255 characters long!" << endl;
        }

        return false;
    }
    else {
        size_t pos = file_name.find_first_of(kForbiddenFileNameCharacters);

        if (pos != string::npos) {
            if (file_name[pos] == '\n' || file_name[pos] == '\t')
            {
                if (verbose) {
                    cout << "File name cannot contain \\t or \\n characters!" << endl;
                }

                return false;
            }
            else {
                if (verbose) {
                    cout << "File name cannot contain " << file_name[pos] << " character!" << endl;
                }

                return false;
            }
        }

        if (file_name.length() == 3) {
            for (int i = 0; i < 4; i++) {
                if (file_name == kForbiddenFileNames3[i]) {
                    if (verbose) {
                        cout << "File name " << file_name << " not allowed!" << endl;
                    }

                    return false;
                }
            }
        }
        else if (file_name.length() == 4) {
            for (int i = 0; i < 18; i++) {
                if (file_name == kForbiddenFileNames4[i]) {
                    if (verbose) {
                        cout << "File name " << file_name << " not allowed!";
                    }

                    return false;
                }
            }
        }

        if (file_name[file_name.length() - 1] == ' ' or
            file_name[file_name.length() - 1] == '.') {
            if (verbose) {
                cout << "File name cannot end with " << file_name[file_name.length() - 1] << " character!" << endl;
            }

            return false;
        }

        return true;
    }
}

bool CheckIfPositiveLong(string str, bool verbose) {
    string size_max_str = to_string(LONG_MAX);

    if (str.length() == 0) {
        if (verbose) {
            cout << "Not a number!" << endl;
        }

        return false;
    }
    else if (str[0] == '-') {
        if (str.length() == 1) {
            if (verbose) {
                cout << "Not a number!" << endl;
            }

            return false;
        }

        if (verbose) {
            cout << "Enter a positive number!" << endl;
        }

        return false;
    }
    else if (str.length() > size_max_str.length()) {
        if (verbose) {
            cout << "Enter a smaller number!" << endl;
        }

        return false;
    }
    else if (str.length() == size_max_str.length()) {
        for (size_t i = 0; i < str.length(); i++) {
            if (!isdigit(static_cast<unsigned char>(str[i]))) {
                if (verbose) {
                    cout << "Not an integer number!" << endl;
                }

                return false;
            }
            else if (str[i] > size_max_str[i]) {
                if (verbose) {
                    cout << "Enter a smaller number!" << endl;
                }

                return false;
            }
        }

        return true;
    }
    else {
        for (size_t i = 0; i < str.length(); i++) {
            if (!isdigit(static_cast<unsigned char>(str[i]))) {
                if (verbose) {
                    cout << "Not an integer number!" << endl;
                }

                return false;
            }
        }

        return true;
    }
}