#include "display.hpp"

#include "text.hpp"

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

void Display::load_current_char() {
    byte numeral = buffer[currentPos];
    byte position = DIGIT_POSITIONS[currentPos];
    PORTD_write(LATCH_PIN, LOW);
    for (byte i = 0; i < 8; i++) { // 7 to 0
        PORTD_write(CLOCK_PIN, LOW);
        PORTB_write(DATA_PIN, is_bit_set(numeral, i));
        PORTD_write(CLOCK_PIN, HIGH);
    }
    for (byte i = 0; i < 8; i++) { // 7 to 0
        PORTD_write(CLOCK_PIN, LOW);
        PORTB_write(DATA_PIN, is_bit_set(position, i));
        PORTD_write(CLOCK_PIN, HIGH);
    }
    PORTD_write(LATCH_PIN, HIGH);
}

Display::Display() : currentPos(0) { }

Display::Display(word number) : Display() {
    write_number(number);
}

Display::Display(char* string) : Display() {
    write_string(string);
}

void Display::write_number(word number) {
    if (number > 9999) number = 9999;

    for (byte i = 0; i < DIGITS_COUNT; i++) {
        byte index = number % 10;
        byte digit = NUMERALS[index];
        buffer[i] = digit;
        number /= 10;
    }
}

void Display::write_string(char* string) {
    for (byte i = 0; i < DIGITS_COUNT; i++) {
        byte letter = string[i];
        byte subtract = ((letter > 'Z') ? 'a' : 'A');
        byte index = letter - subtract;
        byte ch = CHARS[index];
        buffer[i] = ch;
    }
}

void Display::refresh() {
    load_current_char();
    ++currentPos %= DIGITS_COUNT;
}