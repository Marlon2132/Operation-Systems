#include "FactorialClass.h"

using namespace std;

void FactorialClass::setN(long long n) {
	if (n <= 0) {
		throw invalid_argument("[FactorialClass::setN] -> n should be natural!");
	}
	else if (n > 20) {
		throw out_of_range("[FactorialClass::setN] -> n should be <= 20");
	}
	else {
		n_ = n;
	}
}

const unsigned char FactorialClass::getN() const {
	return n_;
}

void FactorialClass::fillFactValues() {
	if (!n_) {
		throw invalid_argument("[FactorialClass::fillFactValues] -> n should be entered before filling!");
	}
	else {
		fact_values_.clear();
		fact_values_.resize(n_);

		fact_values_[0] = 1;

		for (unsigned char i = 1; i < n_; i++) {
			fact_values_[i] = fact_values_[i - 1] * (i + 1);
		}
	}
}

const vector<unsigned long long>& FactorialClass::getFactValues() const {
	if (fact_values_.empty()) {
		throw logic_error("[FactorialClass::getFactValues] -> fact_values is empty");
	}
	else {
		return fact_values_;
	}
}

void FactorialClass::showFactValues() {
	vector<unsigned long long> vec = this->getFactValues();

	cout << endl << "Your fact_values array" << endl
		<< "======================" << endl;

	for (unsigned long long x : vec) {
		cout << x << endl;
	}
}
