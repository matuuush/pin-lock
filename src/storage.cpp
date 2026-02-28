#include "storage.hpp"

#include <avr/eeprom.h>
#include <stdint.h>
#include "constants.hpp"
#include "lock.hpp"

word Storage::read_pin() {
    word pin = eeprom_read_word(PIN_ADDRESS);
    return (pin >= OVERFLOW) ? DEFAULT_CODE : pin;
}

void Storage::write_pin(word new_pin) {
    eeprom_update_word(PIN_ADDRESS, new_pin);
}