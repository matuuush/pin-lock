#ifndef LIGHT_HPP
#define LIGHT_HPP

#include "constants.hpp"

constexpr byte LIGHT_PINS[] = { PB5, PB4, PB3, PB2 };
constexpr byte LIGHTS_COUNT = sizeof(LIGHT_PINS) / sizeof(LIGHT_PINS[0]);

class Light {
private:
	void show_status();
public:
	byte index;
	bool status;
	Light();
	Light(int number);
	void change(bool new_status);
	void change();
};

#endif