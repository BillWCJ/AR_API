#pragma once
#include "pch.h"
#include "Glass.h"

class GlassManager {
public:
	GlassManager();
	~GlassManager();

	int trackGlass();

	uint64_t getTimestamp() { return timestamp.load(); }
	shared_ptr<Vector3> getAccel() { return accel.load(); }
	shared_ptr<Vector3> getGyro() { return gyro.load(); }
	shared_ptr<Vector3> getMag() { return mag.load(); }

	//static DWORD WINAPI StaticThreadStart(void* Param)
	//{
	//	GlassManager* This = (GlassManager*)Param;
	//	return This->ThreadStart();
	//}

	//DWORD ThreadStart(void)
	//{
	//	trackGlass();
	//	return 0;
	//}

	//void startMyThread()
	//{
	//	DWORD ThreadID;
	//	CreateThread(NULL, 0, StaticThreadStart, (void*)this, 0, &ThreadID);
	//}

private:
	shared_ptr<ARGlasses> glasses = nullptr;
	atomic<bool> isTracking = false;

	atomic<uint64_t> timestamp = 0;
	atomic<shared_ptr<Vector3>> accel = make_shared_for_overwrite<Vector3>();
	atomic<shared_ptr<Vector3>> gyro = make_shared_for_overwrite<Vector3>();
	atomic<shared_ptr<Vector3>> mag = make_shared_for_overwrite<Vector3>();
};

struct TrackThreadParams {
	GlassManager* manager;
};
