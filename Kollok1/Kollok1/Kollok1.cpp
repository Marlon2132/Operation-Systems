#include "Kollok1.h"

using namespace std;

int main() {
	try {
		long long n;
		
		cout << "Enter a natural number: ";
		cin >> n;
		
		FactorialClass fact_obj;
		fact_obj.setN(n);
	}
	catch (const ios_base::failure& e) {
		cerr << "Input error: invalid format." << endl;

		return 1;
	}
	catch (const exception& e) {
		cerr << "Error: " << e.what() << endl;

		return 1;
	}
}
