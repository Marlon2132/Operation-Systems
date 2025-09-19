#pragma once
#include <vector>
#include <windows.h>

using namespace std;

struct MinMaxArgs {
	vector<int>* vec;
	int min_element;
	int max_element;
};

struct AverageArgs {
	vector<int>* vec;
	int average;
};

DWORD WINAPI MinMaxProc(LPVOID lpParam);
DWORD WINAPI AverageProc(LPVOID lpParam);
