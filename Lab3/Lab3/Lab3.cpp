#include "Lab3.h"

using namespace std;

int main() {
	try {

		cin.exceptions(ios::failbit | ios::badbit);
		cout << "Enter size of array: ";
		unsigned int n_arr;
		cin >> n_arr;
		vector<int> arr(n_arr, 0);
		cout << "Enter the number of MARKER threads: ";
		unsigned int n_threads;
		cin >> n_threads;
	}
	catch (const ios_base::failure& e) {
		cerr << "Input error: invalid format." << endl;

		return 1;
	}
	catch (const exception& e) {
		cerr << "Error: " << e.what() << endl;

		return 1;
	}

	return 0;
}
