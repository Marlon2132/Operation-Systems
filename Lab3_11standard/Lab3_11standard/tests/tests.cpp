#include <catch2/catch_all.hpp>
#include "../MarkerControl.h"
#include <vector>
#include <chrono>

using namespace std;

static void cleanup(MarkerControl& ctrl) {
    ctrl.start();
    ctrl.stop();
    ctrl.join();
}

TEST_CASE("MarkerControl: getId", "[MarkerControl]") {
    vector<int> arr(5, 0);
    MarkerControl::resetConflicts();
    MarkerControl ctrl(123, arr);

    REQUIRE(ctrl.getId() == 123);

    cleanup(ctrl);
}

TEST_CASE("MarkerControl: waitAllConflicts(0)", "[MarkerControl]") {
    MarkerControl::resetConflicts();
    auto t0 = chrono::steady_clock::now();
    MarkerControl::waitAllConflicts(0);
    auto t1 = chrono::steady_clock::now();
    auto ms = chrono::duration_cast<chrono::milliseconds>(t1 - t0).count();

    REQUIRE(ms < 10);
}

TEST_CASE("MarkerControl: start, waitAllConflicts", "[MarkerControl]") {
    vector<int> arr(1, 0);
    MarkerControl::resetConflicts();
    MarkerControl ctrl(7, arr);
    ctrl.start();
    MarkerControl::waitAllConflicts(1);

    REQUIRE(arr[0] == 7);

    cleanup(ctrl);
}

TEST_CASE("MarkerControl: two conflicts", "[MarkerControl]") {
    vector<int> arr(1, 0);
    MarkerControl::resetConflicts();
    MarkerControl m1(1, arr);
    MarkerControl m2(2, arr);
    m1.start();
    m2.start();
    MarkerControl::waitAllConflicts(2);

    REQUIRE(arr[0] == 1 || arr[0] == 2);

    cleanup(m1);
    cleanup(m2);
}

TEST_CASE("MarkerControl: continueMarker()", "[MarkerControl]") {
    vector<int> arr(1, 0);
    MarkerControl::resetConflicts();
    MarkerControl ctrl(21, arr);
    ctrl.start();
    MarkerControl::waitAllConflicts(1);

    REQUIRE(arr[0] == 21);

    MarkerControl::resetConflicts();
    ctrl.continueMarker();
    MarkerControl::waitAllConflicts(1);

    REQUIRE(arr[0] == 21);

    cleanup(ctrl);
}

TEST_CASE("MarkerControl: stop()+join()", "[MarkerControl]") {
    vector<int> arr(1, 0);
    MarkerControl::resetConflicts();
    MarkerControl ctrl(42, arr);
    ctrl.start();
    MarkerControl::waitAllConflicts(1);

    REQUIRE(arr[0] == 42);

    ctrl.stop();
    ctrl.join();

    REQUIRE(arr[0] == 0);
}

TEST_CASE("MarkerControl: join()", "[MarkerControl]") {
    vector<int> arr(1, 0);
    MarkerControl::resetConflicts();
    MarkerControl ctrl(99, arr);
    ctrl.start();
    MarkerControl::waitAllConflicts(1);

    REQUIRE_NOTHROW(ctrl.join());
    REQUIRE_NOTHROW(ctrl.join());
}
