#include <vector>
#include <unordered_set>
#include <stdexcept>
#include <iostream>

using namespace std;

class VecClass {
private:
	vector<long double> arr_;
	vector<long double> set_arr_;

public:
	void resetArr(long long l);
	void fillArr(unsigned long long i, long double n);
	const vector<long double>& getArr() const;

	void fillSetArr();
	const vector<long double>& getSetArr() const;
	void showSetArr();
};