#include <iostream>
//#include "../api/AirAPI_Windows.h"
#include "../deps/hidapi-win/include/hidapi.h"
#include <mutex>
#include <array>
#include <windows.h>
#include <cstdint>
#include <vector>
#include "../api/AR_API.h"
using namespace std;


int main()
{
	cout << "start: " << StartConnection();

	for (int i = 0; i < 100; i++) {
		float* accel = GetRawAccel();
		float* gyro = GetRawGyro();
		float* mag = GetRawMag();
		cout << "accel: " << accel[0] << ", " << accel[1] << ", " << accel[2] << endl;
		cout << "gyro: " << gyro[0] << ", " << gyro[1] << ", " << gyro[2] << endl;
		cout << "mag: " << mag[0] << ", " << mag[1] << ", " << mag[2] << endl;

		Sleep(1000);
	}

	cout << "stop: " << StopConnection();
}