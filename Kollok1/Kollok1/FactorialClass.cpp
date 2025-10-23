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
		cerr << "Error [FactorialClass::setN]: " << e.what() << endl;

		return;
	}
}

const long long FactorialClass::getN() {
	try {
		return n_;
	}
	catch (const exception& e) {
		cerr << "Error [FactorialClass::getN]: " << e.what() << endl;

		return;
	}
}

void FactorialClass::fillFactValues() {
	try {
		if (n_ <= 0) {
			throw invalid_argument("n should be natural!");
		}
		else {
			this->fact_values_.clear();
			this->fact_values_.reserve(n_);

			this->fact_values_[0] = 1;

			for (unsigned long long i = 1; i < n_; i++) {
				this->fact_values_[i] = this->fact_values_[i - 1] * (i + 1);
			}
		}
	}
	catch (const exception& e) {
		cerr << "Error [FactorialClass::fillFactValues]: " << e.what() << endl;

		return;
	}
}

const vector<unsigned long long>& FactorialClass::getFactValues() const {
	try {
		return fact_values_;
	}
	catch (const exception& e) {
		cerr << "Error [FactorialClass::getFactValues]: " << e.what() << endl;

		return;
	}
}

void FactorialClass::showFactValues() {
	try {
		if (fact_values_.empty()) {
			cout << "Your fact_values array is empty!";
		}
		else {
			cout << "Your fact_values array" << endl
				<< "======================" << endl;

			for (unsigned long long x : fact_values_) {
				cout << x << endl;
			}
		}
	}
	catch (const exception& e) {
		cerr << "Error [FactorialClass::getFactValues]: " << e.what() << endl;

		return;
	}
}
