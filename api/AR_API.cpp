#include "pch.h"
#include "AR_API.h"
#include "GlassManager.h"

using namespace std;

atomic<shared_ptr<GlassManager>> manager;
HANDLE trackThread2;


DWORD WINAPI track2(LPVOID lpParam) {
	manager.load().get()->trackGlass();
	return 0;
}


//Function to start connection to Air
int StartConnection() {
	try {
		manager = std::make_shared<GlassManager>();
		TrackThreadParams trackParams = { manager.load().get()};
		trackThread2 = CreateThread(NULL, 0, track2, &trackParams, 0, NULL);
		if (trackThread2 == NULL) {
			std::cout << "Failed to create thread" << std::endl;
			return 1;
		}
	}
	catch (...) {
		cerr << "can't create manager" << endl;
		return 1;
	}
	return 0;
}

//Function to stop connection to Air
int StopConnection() {
	// free manager
	if (!trackThread2) {
		WaitForSingleObject(trackThread2, INFINITE);
		TerminateThread(trackThread2, 0);
		CloseHandle(trackThread2);
	}

	manager.load().reset();
	return 0;
}

float* q = new float[4];
//Function to get quaternion
float* GetQuaternion() {
	return q;
}

float* e = new float[3];
//Function to get euler
float* GetEuler() {
	return e;
}

float* rawAccel = new float[3];
//Function to get rawAccel
float* GetRawAccel() {
	shared_ptr<Vector3> accel = manager.load().get()->getAccel();
	rawAccel = new float[3] { accel->axis.x, accel->axis.y, accel->axis.z };
	return rawAccel;
}

float* rawGyro = new float[3];
//Function to get rawGyro
float* GetRawGyro() {
	shared_ptr<Vector3> gyro = manager.load().get()->getGyro();
	rawGyro = new float[3]{ gyro->axis.x, gyro->axis.y, gyro->axis.z };
	return rawGyro;
}

float* rawMag = new float[3];
//Function to get rawMag
float* GetRawMag() {
	shared_ptr<Vector3> mag = manager.load().get()->getMag();
	rawMag = new float[3]{ mag->axis.x, mag->axis.y, mag->axis.z };
	return rawMag;
}

uint64_t ts = 0;
//funtion to get timestamp
uint64_t GetAirTimestamp() {
	ts = manager.load().get()->getTimestamp();
	return ts;
}

//Function to get brightness
int GetBrightness() {
	return 0;
}

//Function to set fusion gain
int SetFusionGain(float) {
	return 0;
}

//Function to set accel rejection
int SetFusionAccelRejection(float) {
	return 0;
}

//Function to set mag rejection 
int SetFusionMagRejection(float) {
	return 0;
}

//Function to set mag rejection 
int SetFusionRejectTimeout(unsigned int) {
	return 0;
}

int64_t* rejctionCountersOut = new int64_t[2];
//Function to get rejection counters
int64_t* GetRejectionCounters() {
	return rejctionCountersOut;
}

float* rejectionErrorDegrees = new float[2];
//Function to get accel and mag error values in degrees
float* GetRejectionErrorDegrees() {
	return rejectionErrorDegrees;
}
