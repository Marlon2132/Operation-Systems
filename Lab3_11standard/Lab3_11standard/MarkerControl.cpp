#include "MarkerControl.h"

using namespace std;

boost::mutex MarkerControl::conflictMtx_;
boost::condition_variable MarkerControl::conflictCv_;
unsigned int MarkerControl::conflictCount_ = 0;

MarkerControl::MarkerControl(unsigned int id, vector<int>& arr) :
    id_(id),
    arr_(arr),
    stopFlag_(false),
    continueFlag_(false),
    started_(false)
{
    thr_ = boost::thread(&MarkerControl::marker, this);
}

MarkerControl::~MarkerControl() {
    if (thr_.joinable()) {
        stop();
        continueMarker();
        thr_.join();
    }
}

unsigned int MarkerControl::getId() const {
    return id_;
}

void MarkerControl::start() {
    boost::mutex::scoped_lock lk(startMtx_);
    started_ = true;
    startCv_.notify_one();
}

void MarkerControl::stop() {
    boost::mutex::scoped_lock lk(mtx_);
    stopFlag_ = true;
    cv_.notify_one();
}

void MarkerControl::continueMarker() {
    boost::mutex::scoped_lock lk(mtx_);
    continueFlag_ = true;
    cv_.notify_one();
}

void MarkerControl::join() {
    if (thr_.joinable()) {
        thr_.join();
    }
}

void MarkerControl::marker() {
    // Waiting for the "START" signal from main
    boost::mutex::scoped_lock lk(startMtx_);
    startCv_.wait(lk, [this] { return started_; });
    /*WaitForSingleObject(startEvent_, INFINITE);*/
    cout << "Marker " << id_ << " started" << endl;

    srand(id_);

    unsigned placed_count = 0;

    while (true) {
        int idx = rand() % arr_.size();

        if (arr_[idx] == 0) {
            placed_count++;
            boost::this_thread::sleep_for(boost::chrono::milliseconds(5)); // Sleep(5);
            arr_[idx] = id_;
            boost::this_thread::sleep_for(boost::chrono::milliseconds(5));
            continue;

        }
        else {
            cout << "Marker " << id_
                << ", placed=" << placed_count
                << ", conflict at index=" << idx
                << endl;
            boost::mutex::scoped_lock lk(conflictMtx_);
            conflictCount_++;
            conflictCv_.notify_one();
            //this->cannotProceed();
        }

        boost::mutex::scoped_lock lk(mtx_);
        cv_.wait(lk, [this] { return continueFlag_ || stopFlag_; });

        if (stopFlag_) {
            break;
        }

        continueFlag_ = false;

        /*HANDLE h[2] = { continueEvent_, stopEvent_ };
        DWORD ans = WaitForMultipleObjects(2, h, FALSE, INFINITE);

        if (ans == WAIT_OBJECT_0) {
            continue;
        }
        else {
            break;
        }*/
    }

    for (int& v : arr_) {
        if (v == id_) {
            v = 0;
        }
    }

    cout << "Marker " << id_ << " exiting. Total placed=" << placed_count << endl;
}

void MarkerControl::waitAllConflicts(unsigned int count) {
    boost::unique_lock<boost::mutex> lk(conflictMtx_);
    conflictCv_.wait(lk, [&] { return conflictCount_ >= count; });
}

void MarkerControl::resetConflicts() {
    boost::mutex::scoped_lock lk(conflictMtx_);
    conflictCount_ = 0;
}
