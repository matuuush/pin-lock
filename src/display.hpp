#ifndef DISPLAY_HPP
#define DISPLAY_HPP

#include "constants.hpp"

class Text;

//                         A     b     C     d     E     F     G     H     I     J     K     L     M     n     o     P     q     r     S     t     U     v     w   ksi(=)  Y     Z
constexpr byte CHARS[] { 0x88, 0x83, 0xC6, 0xA1, 0x86, 0x8E, 0x82, 0x89, 0xF9, 0xE1, 0x85, 0xC7, 0xC8, 0xAB, 0xA3, 0x8C, 0x98, 0xAF, 0x92, 0x87, 0xC1, 0xE3, 0x81, 0xB6, 0x91, 0xA4 };

//                              0     1     2     3     4     5     6     7     8     9
constexpr byte NUMERALS[] = { 0xC0, 0xF9, 0xA4, 0xB0, 0x99, 0x92, 0x82, 0xF8, 0x80, 0x90 };
constexpr byte DOT_GLYPH = 0x7F;

constexpr byte DIGIT_POSITIONS[] = {0xF1, 0xF2, 0xF4, 0xF8}; // left to r
constexpr word DIGITS_COUNT = sizeof(DIGIT_POSITIONS) / sizeof(DIGIT_POSITIONS[0]);

void PORTD_write(byte pin, byte value);
void PORTB_write(byte pin, byte value);
bool is_bit_set(byte data, byte bit);

class Display {
private:
byte currentPos;
void load_current_char();
public:
    byte buffer[DIGITS_COUNT];
    Display();
    Display(word number);
    Display(char* string);
    void write_cursor(byte position);
    void write_number(word number);
    void write_string(char* string);
    void refresh();
};

#endif