#include "button.hpp"

Button::Button() { }

Button::Button(byte number) : index(number), status(false) {
    DDRC &= ~(1 << BUTTON_PINS[index]);
    PORTC |= (1 << BUTTON_PINS[index]);
}

bool Button::read_input(byte pin) {
    return ((PINC & (1 << pin)) == LOW);
}

bool Button::is_pressed() {
    return read_input(BUTTON_PINS[index]);
}

bool Button::is_triggered() {
    bool immediate_status = is_pressed();
    if (status != immediate_status) {
        status = immediate_status;
        return (status == true);
    }
    return false;
}
