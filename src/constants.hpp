#ifndef CONSTANTS_HPP
#define CONSTANTS_HPP

typedef uint8_t byte;

constexpr byte NUMERALS[10] = {0xC0, 0xF9, 0xA4, 0xB0, 0x99, 0x92, 0x82, 0xF8, 0x80, 0x90};;
constexpr byte DIGIT_POSITIONS[4] = {0xF8, 0xF4, 0xF2, 0xF1};

constexpr byte HIGH = 1;
constexpr byte LOW = 0;

constexpr byte LATCH_PIN = PD4;
constexpr byte CLOCK_PIN = PD7;
constexpr byte DATA_PIN  = PB0;

#endif