#pragma once

//Function to start connection to Air
extern "C" __declspec(dllexport) int StartConnection();

//Function to stop connection to Air
extern "C" __declspec(dllexport) int StopConnection();

//Function to get quaternion
extern "C" __declspec(dllexport) float* GetQuaternion();

//Function to get euler
extern "C" __declspec(dllexport) float* GetEuler();

//Function to get rawAccel
extern "C" __declspec(dllexport) float* GetRawAccel();

//Function to get rawGyro
extern "C" __declspec(dllexport) float* GetRawGyro();

//Function to get rawMag
extern "C" __declspec(dllexport) float* GetRawMag();

//Funtion to get timestamp
extern "C" __declspec(dllexport) uint64_t GetAirTimestamp();

//Function to get brightness
extern "C" __declspec(dllexport) int GetBrightness();

//Function to set fusion gain
extern "C" __declspec(dllexport) int SetFusionGain(float);

//Function to set accel rejection
extern "C" __declspec(dllexport) int SetFusionAccelRejection(float);

//Function to set mag rejection 
extern "C" __declspec(dllexport) int SetFusionMagRejection(float);

//Function to set mag rejection 
extern "C" __declspec(dllexport) int SetFusionRejectTimeout(unsigned int);

//Function to get rejection counters
extern "C" __declspec(dllexport) int64_t * GetRejectionCounters();

//Function to get accel and mag error values in degrees
extern "C" __declspec(dllexport) float* GetRejectionErrorDegrees();
