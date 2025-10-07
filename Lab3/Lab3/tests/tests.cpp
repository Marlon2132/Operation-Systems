#include <catch2/catch_all.hpp>
#include "../MarkerControl.h"

//void ExitTest(MarkerControl& a) {
//    SetEvent(a.getStopEvent());
//    WaitForSingleObject(a.getThreadHandle(), INFINITE);
//    CloseHandle(a.getThreadHandle());
//    CloseHandle(a.getStartEvent());
//    CloseHandle(a.getStopEvent());
//}

static DWORD waitThread(HANDLE hThread, DWORD timeoutMs) {
    return WaitForSingleObject(hThread, timeoutMs);
}

TEST_CASE("MarkerControl: constructor", "[MarkerControl]") {
    unsigned int expectedId = 528;
    MarkerControl a(expectedId);

    REQUIRE(a.getId() == expectedId);
    REQUIRE(a.getStartEvent() != NULL);
    REQUIRE(a.getStopEvent() != NULL);
    REQUIRE(a.getStartEvent() != a.getStopEvent());
    REQUIRE(a.getThreadHandle() != NULL);

    REQUIRE(WaitForSingleObject(a.getStartEvent(), 0) == WAIT_TIMEOUT);
    REQUIRE(WaitForSingleObject(a.getStopEvent(), 0) == WAIT_TIMEOUT);
    REQUIRE(WaitForSingleObject(a.getThreadHandle(), 0) == WAIT_TIMEOUT);

    //ExitTest(a);
}

TEST_CASE("MarkerControl: getId", "[MarkerControl]") {
    const unsigned int expectedId = 123;
    MarkerControl a(expectedId);

    REQUIRE(a.getId() == expectedId);

    //ExitTest(a);
}

TEST_CASE("MarkerControl: getStartEvent", "[MarkerControl]") {
    MarkerControl a(1);

    REQUIRE(a.getStartEvent() != NULL);
    REQUIRE(WaitForSingleObject(a.getStartEvent(), 0) == WAIT_TIMEOUT);

    //ExitTest(a);
}

TEST_CASE("MarkerControl: getStopEvent", "[MarkerControl]") {
    MarkerControl a(2);

    REQUIRE(a.getStopEvent() != NULL);
    REQUIRE(WaitForSingleObject(a.getStopEvent(), 0) == WAIT_TIMEOUT);

    //ExitTest(a);
}

TEST_CASE("MarkerControl: getThreadHandle", "[MarkerControl]") {
    MarkerControl a(3);

    REQUIRE(a.getThreadHandle() != NULL);
    REQUIRE(WaitForSingleObject(a.getThreadHandle(), 0) == WAIT_TIMEOUT);

    //ExitTest(a);
}