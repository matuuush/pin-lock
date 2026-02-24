#ifndef CONSTANTS_HPP
#define CONSTANTS_HPP

#include <avr/io.h>
#include <util/delay.h>

typedef uint8_t byte;
typedef uint16_t word;

constexpr byte HIGH = 1;
constexpr byte LOW = 0;

constexpr byte LATCH_PIN = PD4;
constexpr byte CLOCK_PIN = PD7;
constexpr byte DATA_PIN  = PB0;

#endif