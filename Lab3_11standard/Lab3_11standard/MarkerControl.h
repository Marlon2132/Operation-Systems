#include <vector>
#include <boost/thread.hpp>
#include <boost/chrono.hpp>
#include <iostream>
#include <cstdlib>
#include <ctime>

using namespace std;

class MarkerControl {
private:
    void marker();

    unsigned int id_;
    vector<int>& arr_;

    boost::thread thr_;
    boost::mutex mtx_;
    boost::condition_variable cv_;
    bool stopFlag_;
    bool continueFlag_;

    boost::mutex startMtx_;
    boost::condition_variable startCv_;
    bool started_;

    static boost::mutex conflictMtx_;
    static boost::condition_variable conflictCv_;
    static unsigned int conflictCount_;

    static boost::mutex arrMtx_;
    static bool firstConflictReported_;

public:
    MarkerControl(unsigned int id, vector<int>& arr);
    ~MarkerControl();

    unsigned int getId() const;
    void start();
    void stop();
    void join();
    void continueMarker();

    static void waitAllConflicts(unsigned int count);
    static void resetConflicts();
};
