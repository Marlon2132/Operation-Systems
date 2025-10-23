#include "MarkerControl.h"

using namespace std;

boost::mutex MarkerControl::conflictMtx_;
boost::condition_variable MarkerControl::conflictCv_;
unsigned int MarkerControl::conflictCount_ = 0;
boost::mutex MarkerControl::arrMtx_;
bool MarkerControl::firstConflictReported_ = false;

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
    boost::mutex::scoped_lock startLock(startMtx_);
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
    {
        boost::mutex::scoped_lock startLock(startMtx_);
        startCv_.wait(startLock, [this] { return started_; });
    }

    {
        boost::mutex::scoped_lock arrLock(arrMtx_);
        std::cout << "Marker " << id_ << " started" << std::endl;
    }

    srand(id_);
    unsigned placed_count = 0;

    while (true) {
        int idx = rand() % arr_.size();

        boost::mutex::scoped_lock arrLock(arrMtx_);

        if (arr_[idx] == 0) {
            placed_count++;
            boost::this_thread::sleep_for(boost::chrono::milliseconds(5));
            arr_[idx] = static_cast<int>(id_);
            boost::this_thread::sleep_for(boost::chrono::milliseconds(5));
            arrLock.unlock();
            continue;
        }
        else {
            std::cout << "Marker " << id_
                << ", placed=" << placed_count
                << ", conflict at index=" << idx
                << std::endl;
        }

        arrLock.unlock();

        {
            boost::mutex::scoped_lock conflictLock(conflictMtx_);
            ++conflictCount_;
            conflictCv_.notify_one();
        }

        {
            boost::mutex::scoped_lock controlLock(mtx_);
            cv_.wait(controlLock, [this] { return continueFlag_ || stopFlag_; });

            if (stopFlag_) {
                break;
            }

            firstConflictReported_ = false;

            continueFlag_ = false;
        }
    }

    {
        boost::mutex::scoped_lock arrLock(arrMtx_);
        for (int& v : arr_) {
            if (v == static_cast<int>(id_)) v = 0;
        }
        std::cout << "Marker " << id_ << " exiting. Total placed=" << placed_count << std::endl;
    }
}


void MarkerControl::waitAllConflicts(unsigned int count) {
    boost::unique_lock<boost::mutex> lk(conflictMtx_);
    conflictCv_.wait(lk, [&] { return conflictCount_ >= count; });
}

void MarkerControl::resetConflicts() {
    boost::mutex::scoped_lock conflictLock(conflictMtx_);
    conflictCount_ = 0;
    boost::mutex::scoped_lock arrLock(arrMtx_);
    firstConflictReported_ = false;
}
