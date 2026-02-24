#ifndef BUTTON_HPP
#define BUTTON_HPP

#include "constants.hpp"

constexpr int BUTTON_PINS[] = { PC1, PC2, PC3 };
constexpr int BUTTON_COUNT = sizeof(BUTTON_PINS) / sizeof(BUTTON_PINS[0]);

class Button {
public:
    
    int index;
    bool status;
    
    Button() { }
    Button(int number) : index(number), status(false) {
        DDRC &= ~(1 << BUTTON_PINS[index]);
        PORTC |= (1 << BUTTON_PINS[index]);
        /*DDRC &= ~((1 << PC1) | (1 << PC2) | (1 << PC3));
        PORTC |= ((1 << PC1) | (1 << PC2) | (1 << PC3));*/
    }

    bool read_input(byte pin) {
        return ((PINC & (1 << pin)) == 0);
    }
    
    bool is_pressed() {
        return (read_input(BUTTON_PINS[index]) == LOW);
    }
    
    bool is_triggered() {
        bool immediate_status = is_pressed();
        if (status != immediate_status) {
            status = immediate_status;
            return (status == true);
        }
        return false;
    }
    
    bool is_released() {
        bool immediate_status = is_pressed();
        if (status != immediate_status) {
            status = immediate_status;
            return (status == false);
        }
        return false;
    }
};

#endif