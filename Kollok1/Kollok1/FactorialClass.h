#include <iostream>
#include <vector>

using namespace std;

class FactorialClass {
private:
	unsigned char n_ = 0;
	vector<unsigned long long> fact_values_;

public:
	void setN(long long n);
	const unsigned char getN() const;

	void fillFactValues();
	const vector<unsigned long long>& getFactValues() const;
	void showFactValues();
};