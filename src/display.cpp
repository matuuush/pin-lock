#include "display.hpp"

#include "lock.hpp"

void Display::load_current_char() {
    byte numeral = buffer[currentPos];
    byte position = DIGIT_POSITIONS[currentPos];
    PORTD_write(LATCH_PIN, LOW);
    for (byte i = 0; i < 8; i++) {
        PORTD_write(CLOCK_PIN, LOW);
        PORTB_write(DATA_PIN, is_bit_set(numeral, 8 - i - 1));
        PORTD_write(CLOCK_PIN, HIGH);
    }
    for (byte i = 0; i < 8; i++) {
        PORTD_write(CLOCK_PIN, LOW);
        PORTB_write(DATA_PIN, is_bit_set(position, 8 - i - 1));
        PORTD_write(CLOCK_PIN, HIGH);
    }
    PORTD_write(LATCH_PIN, HIGH);
}

Display::Display() : currentPos(0) {
    DDRD |= (1 << LATCH_PIN) | (1 << CLOCK_PIN);
    DDRB |= (1 << DATA_PIN);
}

Display::Display(word number) : Display() {
    write_number(number);
}

Display::Display(const char* string) : Display() {
    write_string(string);
}

void Display::write_cursor(byte position) {
    //buffer[position] &= DOT_GLYPH; // dot is on the first bit
    byte prev_pos = currentPos;
    currentPos = position;
    load_current_char();
    currentPos = prev_pos;
}

void Display::write_number(word number) {
    for (byte i = 0; i < DIGITS_COUNT; i++) {
        byte index = number % NUMERAL_BASIS;
        byte digit = NUMERALS[index];
        buffer[DIGITS_COUNT - i - 1] = digit;
        number /= NUMERAL_BASIS;
    }
}

void Display::write_string(const char* string) {
    for (byte i = 0; i < DIGITS_COUNT; i++) {
        byte letter = string[i];
        byte subtract = ((letter > 'Z') ? 'a' : 'A');
        byte index = letter - subtract;
        byte ch = CHARS[index];
        buffer[i] = (letter == ' ') ? SPACE_CHAR : ch;
    }
}

void Display::refresh() {
    load_current_char();
    ++currentPos %= DIGITS_COUNT;
}