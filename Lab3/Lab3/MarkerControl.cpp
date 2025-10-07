#include "MarkerControl.h"

MarkerControl::MarkerControl(unsigned int id) : id_(id) {
	startEvent_ = CreateEvent(
		NULL,
		TRUE,
		FALSE,
		NULL);
	stopEvent_ = CreateEvent(
		NULL,
		TRUE,
		FALSE,
		NULL);
	threadHandle_ = CreateThread(
		NULL,
		0,
		&MarkerControl::ThreadProc,
		this,
		0,
		NULL
	);
}

DWORD WINAPI MarkerControl::ThreadProc(LPVOID param) {
	return static_cast<MarkerControl*>(param)->marker();
}

DWORD MarkerControl::marker() {
	// Waiting for the "START" signal from main
	WaitForSingleObject(startEvent_, INFINITE);
	cout << "Marker " << id_ << " started\n";

	// until STOP
	while (WaitForSingleObject(stopEvent_, 0) == WAIT_TIMEOUT) {
		// marker logic hasn't been implemented yet
		Sleep(100);
	}

	cout << "Marker " << id_ << " exiting\n";
	return 0;
}

unsigned int MarkerControl::getId() {
	return id_;
}

HANDLE MarkerControl::getStartEvent() {
	return startEvent_;
}

HANDLE MarkerControl::getStopEvent() {
	return stopEvent_;
}
HANDLE MarkerControl::getThreadHandle() {
	return threadHandle_;
}