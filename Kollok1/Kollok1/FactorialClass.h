#include <iostream>
#include <vector>

using namespace std;

class FactorialClass {
private:
	long long n_;
	vector<unsigned long long> fact_values_;

public:
	void setN(long long n);
	const long long getN();

	void fillFactValues();
	const vector<unsigned long long>& getFactValues() const;
	void showFactValues();
};