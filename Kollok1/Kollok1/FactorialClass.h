#include <iostream>

using namespace std;

class FactorialClass {
private:
	long long n_;
	unsigned long long fact_value_;

public:
	void setN(long long n);
	long long getN();

	void setFactValue(unsigned long long fact_value);
	unsigned long long getFactValue();
};