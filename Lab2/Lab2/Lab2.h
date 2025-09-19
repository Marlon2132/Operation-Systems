#pragma once
#include <vector>
#include <windows.h>

using namespace std;

struct MinMaxArgs {
	vector<long long>* vec;
	long long min_element;
	long long max_element;
};

struct AverageArgs {
	vector<long long>* vec;
	long long average;
};

DWORD WINAPI MinMaxProc(LPVOID lpParam);
DWORD WINAPI AverageProc(LPVOID lpParam);
