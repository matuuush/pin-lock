#ifndef CONSTANTS_HPP
#define CONSTANTS_HPP

#include <avr/io.h>
#include <util/delay.h>

typedef uint8_t byte;
typedef uint16_t word;

constexpr word DEFAULT_CODE = 0;

constexpr byte HIGH = 1;
constexpr byte LOW = 0;

constexpr byte FIRST = 0;
constexpr byte SECOND = 1;
constexpr byte THIRD = 2;

constexpr byte NUMERAL_BASIS = 10;

void PORTD_write(byte pin, byte value);
void PORTB_write(byte pin, byte value);
bool is_bit_set(byte data, byte bit);
word power_function(byte base, byte exponent);

#endif