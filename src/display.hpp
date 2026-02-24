#ifndef DISPLAY_HPP
#define DISPLAY_HPP

#include "constants.hpp"

class Text;

//                         A     b     C     d     E     F     G     H     I     J     K     L     M     n     o     P     q     r     S     t     U     v     w   ksi(=)  Y     Z
constexpr byte CHARS[] { 0x88, 0x83, 0xC6, 0xA1, 0x86, 0x8E, 0x82, 0x89, 0xF9, 0xE1, 0x85, 0xC7, 0xC8, 0xAB, 0xA3, 0x8C, 0x98, 0xAF, 0x92, 0x87, 0xC1, 0xE3, 0x81, 0xB6, 0x91, 0xA4 };

//                               0     1     2     3     4     5     6     7     8     9
constexpr byte NUMERALS[10] = {0xC0, 0xF9, 0xA4, 0xB0, 0x99, 0x92, 0x82, 0xF8, 0x80, 0x90};
constexpr byte DIGIT_POSITIONS[] = {0xF8, 0xF4, 0xF2, 0xF1}; // left to r
constexpr int DISPLAY_POSITIONS = sizeof(DIGIT_POSITIONS) / sizeof(DIGIT_POSITIONS[0]);

void PORTD_write(byte pin, byte value);
void PORTB_write(byte pin, byte value);
bool is_bit_set(byte byte, int bit);

class Display {
private:
    byte buffer[4];
    byte currentPos;
    void load_current_char();
public:
    Display();
    Display(int number);
    Display(Text t);
    void write_number(int number);
    void write_string(Text t);
    void refresh();
};

#endif