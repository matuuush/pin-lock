#include "constants.hpp"

void PORTD_write(byte pin, byte value) {
    if (value == LOW) {
        PORTD &= ~(1 << pin);
    } else if (value == HIGH) {
        PORTD |= (1 << pin);
    }
}

void PORTB_write(byte pin, byte value) {
    if (value == LOW) {
        PORTB &= ~(1 << pin);
    } else if (value == HIGH) {
        PORTB |= (1 << pin);
    }
}

bool is_bit_set(byte data, byte bit) {
    return data & (1 << bit);
}

word power_function(byte base, byte exponent) {
    word result = 1;
    while (exponent-- > 0) {
        result *= base;
    }
    return result;
}