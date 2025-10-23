#include "FactorialClass.h"

using namespace std;

void FactorialClass::setN(long long n) {
	try {
		if (n <= 0) {
			throw invalid_argument("n should be natural!");
		}
		else {
			this->n_ = n;
		}
	}
	catch (const exception& e) {
		cerr << "Error: " << e.what() << endl;

		return;
	}
}

long long FactorialClass::getN() {
	return n_;
}

void FactorialClass::setFactValue(unsigned long long n) {
	try {
		this->fact_value_ = fact_value_;
	}
	catch (const exception& e) {
		cerr << "Error: " << e.what() << endl;

		return;
	}
}

unsigned long long FactorialClass::getFactValue() {
	return fact_value_;
}

unsigned long long FactorialClass::fact(unsigned long long n) {
	if (n == 0) {
		return 1;
	}

	return fact(n - 1) * n;
}