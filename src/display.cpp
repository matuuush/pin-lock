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

bool is_bit_set(byte byte, int bit) {
    return byte & (1 << bit);
}

void Display::load_current_char() {
    byte numeral = buffer[currentPos];
    byte position = DIGIT_POSITIONS[currentPos];
    PORTD_write(LATCH_PIN, LOW);
    for (int i = 7; i >= 0; i--) {
        PORTD_write(CLOCK_PIN, LOW);
        PORTB_write(DATA_PIN, is_bit_set(numeral, i));
        PORTD_write(CLOCK_PIN, HIGH);
    }
    for (int i = 7; i >= 0; i--) {
        PORTD_write(CLOCK_PIN, LOW);
        PORTB_write(DATA_PIN, is_bit_set(position, i));
        PORTD_write(CLOCK_PIN, HIGH);
    }
    PORTD_write(LATCH_PIN, HIGH);
}

Display::Display() : currentPos(0) {
    DDRD |= (1 << LATCH_PIN) | (1 << CLOCK_PIN);
    DDRB |= (1 << DATA_PIN);
}

Display::Display(int number) : Display() {
    write_number(number);
}

Display::Display(Text t) : Display() {
    write_string(t);
}

void Display::write_number(int number) {
    if (number > 9999) number = 9999;

    for (int i = 0; i < DISPLAY_POSITIONS; i++) {
        int index = number % 10;
        byte digit = NUMERALS[index];
        buffer[i] = digit;
        number /= 10;
    }
}

void Display::write_string(Text t) {
    char* string = t.get();
    for (int i = 0; i < DISPLAY_POSITIONS; i++) {
        byte letter = string[i];
        byte subtract = ((letter > 'Z') ? 'a' : 'A');
        byte index = letter - subtract;
        byte ch = CHARS[index];
        buffer[i] = ch;
    }
}

void Display::refresh() {
    load_current_char();
    ++currentPos %= DISPLAY_POSITIONS;
}