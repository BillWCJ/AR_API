#pragma once
#include "../deps/hidapi-win/include/hidapi.h"
#include "Glass.h"

using namespace std;

#pragma pack(push, 1)
struct AirDataPacket {

	uint8_t signature[2];
	uint8_t temperature[2];
	uint64_t timestamp;
	uint8_t angular_multiplier[2];
	uint8_t angular_divisor[4];
	uint8_t angular_velocity_x[3];
	uint8_t angular_velocity_y[3];
	uint8_t angular_velocity_z[3];
	uint8_t acceleration_multiplier[2];
	uint8_t acceleration_divisor[4];
	uint8_t acceleration_x[3];
	uint8_t acceleration_y[3];
	uint8_t acceleration_z[3];
	uint8_t magnetic_multiplier[2];
	uint8_t magnetic_divisor[4];
	uint8_t magnetic_x[2];
	uint8_t magnetic_y[2];
	uint8_t magnetic_z[2];
	uint32_t checksum;
	uint8_t _padding[7];
};
#pragma pack(pop)

class XrealAir : public ARGlasses {

public:
	XrealAir();
	~XrealAir() override;

	int read_event(GlassesEvent* event) override;

	const char* name() override {
		return "Xreal Air";
	}
	uint64_t display_delay() override {
		return 7000;
	}
	unsigned short vendor_id() override {
		return 0x3318;
	}
	unsigned short product_id() override {
		return 0x0424;
	}

private:
	atomic<shared_ptr<hid_device>> device;
};

