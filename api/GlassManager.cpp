#include "pch.h"
#include "Glass.h"
#include "XRealAirGlass.h"
#include "GlassManager.h"

GlassManager::GlassManager() {
	glasses = make_shared<XrealAir>();

	if (!glasses) {
		cout << "Unable to open glasses" << endl;
		throw std::runtime_error("Unable to open glasses");
	}

	cout << "Glasses opened" << endl;
	isTracking = true;
}

int GlassManager::trackGlass() {
	while (isTracking) {
		GlassesEvent event = {};
		int res = glasses->read_event(&event);
		if (res != 0) {
			cerr << "Unable to read event" << endl;
		}

		timestamp = event.timestamp;

		accel = make_shared<Vector3>(event.accel);
		gyro = make_shared<Vector3>(event.gyro);
		mag = make_shared<Vector3>(event.mag);
	}
	return 0;
}

GlassManager::~GlassManager() {
	if (isTracking) {
		isTracking = false;
		// Wait for the track thread to finish
		//WaitForSingleObject(trackThread, INFINITE);
		//TerminateThread(trackThread, 0);
		//CloseHandle(trackThread);
	}

	if (glasses != nullptr) {
		glasses->~ARGlasses();
	}
}

GlassManager* createGlassManager() {
	try {
		GlassManager m = GlassManager();
		return &m;
	}
	catch (exception e) {

		cout << e.what() << endl;
		return nullptr;
	}
	catch (...) {
		cout << "Unknown error in createGlassManager" << endl;
		return nullptr;
	}
}

int destroyGlassManager(GlassManager* manager) {
	try {
		manager->~GlassManager();
		return 0;
	}
	catch (exception e) {

		cout << e.what() << endl;
		return 1;
	}
	catch (...) {
		cout << "Unknown error in createGlassManager" << endl;
		return 2;
	}
}