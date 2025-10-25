#include "VecClass.h"

using namespace std;

void VecClass::resetArr(long long l) {
	if (l <= 0) {
		throw invalid_argument("[VecClass::resetArr] -> length of array should be > 0");
	}
	else {
		arr_.clear();
		arr_.resize(l);
	}
}

void VecClass::fillArr(unsigned long long i, long double n) {
	if (i >= arr_.size()) {
		throw invalid_argument("[VecClass::fillArr] -> index of element should be > 0 and < length of arr");
	}
	else {
		arr_[i] = n;
	}
}

const vector<long double>& VecClass::getArr() const {
	if (arr_.empty()) {
		throw logic_error("[VecClass::getArr] -> arr is empty");
	}
	else {
		return arr_;
	}
}

void VecClass::fillSetArr() {
	if (arr_.empty()) {
		throw logic_error("[VecClass::fillSetArr] -> arr is empty");
	}
	else {
		set_arr_.clear();
		set_arr_.reserve(arr_.size());

		unordered_set<long double> seen;

		for (double long x : arr_) {
			if (seen.insert(x).second) {
				set_arr_.push_back(x);
			}
		}
	}
}

const vector<long double>& VecClass::getSetArr() const {
	if (arr_.empty()) {
		throw logic_error("[VecClass::getSetArr] -> set_arr is empty");
	}
	else {
		return set_arr_;
	}
}

void VecClass::showSetArr() {
	vector<long double> vec = this->getSetArr();

	cout << endl << "Your new array (length = " << vec.size() << ")" << endl
		<< "======================" << endl;

	for (long double x : vec) {
		cout << x << endl;
	}
}