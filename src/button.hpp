#ifndef BUTTON_HPP
#define BUTTON_HPP

#include "constants.hpp"

constexpr byte BUTTON_PINS[] = { PC1, PC2, PC3 };
constexpr byte BUTTON_COUNT = sizeof(BUTTON_PINS) / sizeof(BUTTON_PINS[0]);

class Button {
public:
    byte index;
    bool status;
    Button();
    Button(byte number);
    bool read_input(byte pin);
    bool is_pressed();
    bool is_triggered();
};

#endif