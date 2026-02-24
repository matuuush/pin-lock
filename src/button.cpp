#include "button.hpp"

Button::Button() { }
Button::Button(byte number) : index(number), status(false) {
    DDRC &= ~(1 << BUTTON_PINS[index]);
    PORTC |= (1 << BUTTON_PINS[index]);
    /*DDRC &= ~((1 << PC1) | (1 << PC2) | (1 << PC3));
    PORTC |= ((1 << PC1) | (1 << PC2) | (1 << PC3));*/
}

bool Button::read_input(byte pin) {
    return ((PINC & (1 << pin)) == 0);
}

bool Button::is_pressed() {
    return (read_input(BUTTON_PINS[index]) == LOW);
}

bool Button::is_triggered() {
    bool immediate_status = is_pressed();
    if (status != immediate_status) {
        status = immediate_status;
        return (status == true);
    }
    return false;
}

bool Button::is_released() {
    bool immediate_status = is_pressed();
    if (status != immediate_status) {
        status = immediate_status;
        return (status == false);
    }
    return false;
}