#include <avr/io.h>
#include <util/delay.h>
#include "constants.hpp"

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

class Display {
    static constexpr int POSITIONS = 4;
private:
    byte buffer[4];
    byte currentPos;
    void load_current_char() {
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

public:
    Display() {
        DDRD |= (1 << LATCH_PIN) | (1 << CLOCK_PIN);
        DDRB |= (1 << DATA_PIN);
        currentPos = 0;
    }
    Display(int number) {
        Display();
        write_number(number);
    }
    /*Display(std::string str) {
        Display();
        write_string(str);
    }*/

    void write_number(int number) {
        if (number > 9999) number = 9999;

        for (int i = 0; i < POSITIONS; i++) {
            int index = number % 10;
            byte digit = NUMERALS[index];
            buffer[i] = digit;
            number /= 10;
        }
    }

    /*void write_string(std::string str) {
        if (str.len > POSITIONS) str = str.substr(0, 4);

        for (int i = 0; i < POSITIONS; i++) {
            int index = number % 10;
            byte digit = NUMERALS[index];
            buffer[i] = digit;
            number /= 10;
        }
    }*/

    void refresh() {
        load_current_char();
        ++currentPos %= POSITIONS;
    }
};

int main(void) {
    Display myDisplay(1234);
    
    int index = 0;
    while (true) {
        myDisplay.write_number(index++);
        myDisplay.refresh();
        _delay_ms(100); 
    }
    
    return 0;
}