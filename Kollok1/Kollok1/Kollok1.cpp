#include "Kollok1.h"
#include "VecClass.h"
#include "LinkedList.h"

using namespace std;

int main() {
	try {
		//Task1
		long long n;
		
		cout << "Enter a natural number: ";
		cin >> n;
		
		FactorialClass fact_obj;

		fact_obj.setN(n);
		fact_obj.fillFactValues();
		fact_obj.showFactValues();

		//Task2
		long long arr_len;

		cout << endl << endl
			<< endl << "Enter the natural length of array: ";
		cin >> arr_len;

		VecClass v;
		v.resetArr(arr_len);

		long double x;
		cout << endl << "Enter the array of long double ("
			<< arr_len << " elements):" << endl;

		for (unsigned long long i = 0; i < arr_len; i++) {
			cin >> x;
			v.fillArr(i, x);
		}

		v.fillSetArr();
		v.showSetArr();

		//Task3
		long long linked_list_len;

		cout << endl << endl
			<< endl << "Enter the natural length of linked list: ";
		cin >> linked_list_len;

		if (linked_list_len <= 0) {
			throw invalid_argument("[main] -> linked_list length should be > 0");
		}
		else {
			LinkedList list;
			long double y;

			cout << endl << "Enter the list of long double ("
				<< linked_list_len << " elements):" << endl;
			
			for (unsigned long long i = 0; i < linked_list_len; i++) {
				cin >> y;
				list.push_back(y);
			}

			list.print();

			cout << endl << "Reversing..." << endl;

			list.recReverse();

			list.print();
		}

	}
	catch (const ios_base::failure& e) {
		cerr << "Input error: invalid format." << endl;

		return 1;
	}
	catch (const exception& e) {
		cerr << "Error: " << e.what() << endl;

		return 1;
	}
}
