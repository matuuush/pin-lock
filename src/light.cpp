#include "light.hpp"

Light::Light() { }

Light::Light(int number) : index(number), status(false) {
	DDRB |= (1 << LIGHT_PINS[index]);
	PORTB |= (1 << LIGHT_PINS[index]);
}

void Light::show_status() {
	PORTB_write(LIGHT_PINS[index], !status);
}

void Light::change(bool new_status) {
	status = new_status;
	show_status();
}

void Light::change() {
	status = !status;
	show_status();
}
