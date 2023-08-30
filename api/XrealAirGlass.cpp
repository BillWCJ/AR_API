#include "pch.h"
#include "XrealAirGlass.h"
#include <iostream>

using namespace std;

XrealAir::XrealAir() {
	hid_device* d = openHid(vendor_id(), product_id(), 3);

	//c++ convert pointer to shared pointer
	device = shared_ptr<hid_device>(d, [](hid_device* p) { hid_close(p); });
	// check if device is null pointer
	if (device.load().get() == nullptr) {
		cout << "Unable to open: " << name() << endl;
		throw std::runtime_error("Unable to open device");
	}

	cout << "Opened: " << name() << ". Sending Payload" << endl;
	uint8_t magic_payload[] = { 0x00, 0xaa, 0xc5, 0xd1, 0x21, 0x42, 0x04, 0x00, 0x19, 0x01 };
	int res = hid_write(device.load().get(), magic_payload, sizeof(magic_payload));
	if (res < 0) {
		std::cout << "Unable to write to device" << std::endl;
		throw std::runtime_error("Unable to write to device");
	}
}

XrealAir::~XrealAir() {
	// TODO: close hid device
	device.load().reset();
}

int XrealAir::read_event(GlassesEvent* event) {
	AirDataPacket buffer;
	memset(&buffer, 0, sizeof(AirDataPacket));
	try {
		int res = hid_read(device.load().get(), (uint8_t*)&buffer, sizeof(buffer));
		if (res < 0) {
			cout << "Unable to read from device: " << res << endl;
		}
	}
	catch (const std::exception& e) {
		std::cerr << e.what();
	}

	AirDataPacket* packet = &buffer;
	const uint64_t timestamp = packet->timestamp;
	event->timestamp = timestamp;

	// Accel scaling values
	int32_t accel_m = pack16bit_signed(packet->acceleration_multiplier);
	int32_t accel_d = pack32bit_signed(packet->acceleration_divisor);
	// Accel conversion to 32bit signed int
	int32_t accel_x = pack24bit_signed(packet->acceleration_x);
	int32_t accel_y = pack24bit_signed(packet->acceleration_y);
	int32_t accel_z = pack24bit_signed(packet->acceleration_z);
	// Accel scale correction
	float accel_x_cor = (float)accel_x * (float)accel_m / (float)accel_d;
	float accel_y_cor = (float)accel_y * (float)accel_m / (float)accel_d;
	float accel_z_cor = (float)accel_z * (float)accel_m / (float)accel_d;

	event->accel = { accel_x_cor, accel_y_cor, accel_z_cor };

	// Gyro scaling values
	int32_t vel_m = pack16bit_signed(packet->angular_multiplier);
	int32_t vel_d = pack32bit_signed(packet->angular_divisor);
	// Gyro conversion to 32bit signed
	int32_t vel_x = pack24bit_signed(packet->angular_velocity_x);
	int32_t vel_y = pack24bit_signed(packet->angular_velocity_y);
	int32_t vel_z = pack24bit_signed(packet->angular_velocity_z);
	// Gyro scale correction
	float vel_x_cor = (float)vel_x * (float)vel_m / (float)vel_d;
	float vel_y_cor = (float)vel_y * (float)vel_m / (float)vel_d;
	float vel_z_cor = (float)vel_z * (float)vel_m / (float)vel_d;

	event->gyro = { vel_x_cor, vel_y_cor, vel_z_cor };

	// Mag scaling values
	int32_t magnet_m = pack16bit_signed_swap(packet->magnetic_multiplier);
	int32_t magnet_d = pack32bit_signed_swap(packet->magnetic_divisor);
	// Mag conversion to 32bit signed int
	int16_t magnet_x = pack16bit_signed_swap(packet->magnetic_x);
	int16_t magnet_y = pack16bit_signed_swap(packet->magnetic_y);
	int16_t magnet_z = pack16bit_signed_swap(packet->magnetic_z);
	// Mag scale correction
	float mag_x_cor = (float)magnet_x * (float)magnet_m / (float)magnet_d;
	float mag_y_cor = (float)magnet_y * (float)magnet_m / (float)magnet_d;
	float mag_z_cor = (float)magnet_z * (float)magnet_m / (float)magnet_d;

	event->mag = { mag_x_cor, mag_y_cor, mag_z_cor };

	return 0;
}

