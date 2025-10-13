#include "Lab3.h"
#include "MarkerControl.h"

using namespace std;

static void showIntArr(const vector<int>& arr, bool after) {
    cout << "Arr state" << (after ? " after removal:" : ":") << endl;
    
    for (int a : arr) {
        cout << a << " ";
    }

    cout << endl;
}

int main() {
    try {
        cin.exceptions(ios::failbit | ios::badbit);
        cout << "Enter size of array: ";
        unsigned int n_arr;
        cin >> n_arr;
        vector<int> arr(n_arr, 0);
        cout << "Enter the number of MARKER threads: ";
        unsigned int n_threads;
        cin >> n_threads;
        vector<MarkerControl*> threads;
        threads.reserve(n_threads);

        for (unsigned i = 1; i <= n_threads; ++i) {
            threads.push_back(new MarkerControl(i, arr));
        }

        for (MarkerControl* t : threads) {
            t->start();
        }

        while (!threads.empty()) {
            MarkerControl::waitAllConflicts(threads.size());
            MarkerControl::resetConflicts();

            /*vector<HANDLE> barriers;
            barriers.reserve(n_threads);

            for (MarkerControl* t : threads) {
                barriers.push_back(t->getСannotProceedEvent());
            }

            DWORD waitResult = WaitForMultipleObjects(
                threads.size(),
                barriers.data(),
                TRUE,
                INFINITE
            );

            for (MarkerControl* t : threads) {
                t->reset();
            }*/

            showIntArr(arr, false);
            cout << "Enter the sequence number of the marker thread that will be signaled to terminate its operation:" << endl;
            unsigned int id;
            cin >> id;
            auto it = find_if(threads.begin(), threads.end(), [id](MarkerControl* t) { return t->getId() == id; });
            
            if (it == threads.end()) {
                throw out_of_range("Invalid marker id");
            }

            MarkerControl* victim = *it;
            victim->stop();
            victim->join();
            delete victim;
            threads.erase(it);
            cout << "Joined marker " << id << endl;
            showIntArr(arr, true);

            for (MarkerControl* t : threads) {
                t->continueMarker();
            }
        }
    }
    catch (const ios_base::failure&) {
        cerr << "Input error: invalid format." << endl;

        return 1;
    }
    catch (const exception& e) {
        cerr << "Error: " << e.what() << endl;

        return 1;
    }

    return 0;
}
