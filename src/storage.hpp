#ifndef STORAGE_HPP
#define STORAGE_HPP

#include <avr/eeprom.h>
#include <stdint.h>
#include "constants.hpp"

constexpr word* PIN_ADDRESS = (word*) 0x00;
constexpr word EMPTY_VALUE = 0xFFFF;

class Storage {
public:
    word read_pin();
    void write_pin(word new_pin);
};

#endif