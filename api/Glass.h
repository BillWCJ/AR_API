#pragma once

typedef union {
	float array[3];

	struct {
		float x;
		float y;
		float z;
	} axis;
} Vector3;

struct GlassesEvent {
	uint64_t timestamp;
	Vector3 accel;
	Vector3 gyro;
	Vector3 mag;
};

class ARGlasses {
public:
	/// Common interface for AR implemented glasses
	virtual ~ARGlasses() = default;

	/// Get a single sensor event. Blocks.
	virtual int read_event(GlassesEvent* event) = 0;

	virtual const char* name() = 0;

	virtual uint64_t display_delay() = 0;

	virtual unsigned short vendor_id() = 0;

	virtual unsigned short product_id() = 0;

};

static hid_device* openHid(unsigned short vendor_id, unsigned short product_id, int interface_number) {
	struct hid_device_info* devs = hid_enumerate(vendor_id, product_id);
	struct hid_device_info* cur_dev = devs;
	hid_device* device = NULL;

	while (devs) {
		if (cur_dev->interface_number == interface_number) {
			device = hid_open_path(cur_dev->path);
			std::cout << "Interface Found: " << interface_number << std::endl;
			break;
		}

		cur_dev = cur_dev->next;
	}

	hid_free_enumeration(devs);
	return device;
}


static int32_t pack32bit_signed(const uint8_t* data) {
	uint32_t t0v, t1v, t2v, t3v;
	t0v = data[0];
	t1v = (data[1] << 8);
	t2v = (data[2] << 16);
	t3v = (data[3] << 24);

	uint32_t unsigned_value = t0v | t1v | t2v | t3v;
	return static_cast<int32_t>(unsigned_value);
}

static int32_t pack24bit_signed(const uint8_t* data) {
	uint32_t unsigned_value = (data[0]) | (data[1] << 8) | (data[2] << 16);
	if ((data[2] & 0x80) != 0) unsigned_value |= (0xFFu << 24);
	return static_cast<int32_t>(unsigned_value);
}

static int16_t pack16bit_signed(const uint8_t* data) {
	uint32_t t0v, t1v;
	t0v = data[0];
	t1v = (data[1] << 8);

	uint16_t unsigned_value = t0v | t1v;
	return static_cast<int16_t>(unsigned_value);
}

static int32_t pack32bit_signed_swap(const uint8_t* data) {
	uint32_t t0v, t1v, t2v, t3v;
	t0v = data[0] << 24;
	t1v = (data[1] << 16);
	t2v = (data[2] << 8);
	t3v = (data[3]);

	uint32_t unsigned_value = t0v | t1v | t2v | t3v;
	return static_cast<int32_t>(unsigned_value);
}


static int16_t pack16bit_signed_swap(const uint8_t* data) {
	uint32_t t0v, t1v;
	t0v = data[0] << 8;
	t1v = (data[1]);
	uint16_t unsigned_value = t0v | t1v;
	return (int16_t)unsigned_value;
}