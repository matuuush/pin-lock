#include "button.hpp"
#include "constants.hpp"
#include "display.hpp"
#include "lock.hpp"
#include "uart.hpp"

Lock lock;
Display display;
Button buttons[BUTTON_COUNT];
UART serial;

word index = 0;

void init_pins() {
    DDRD |= (1 << LATCH_PIN) | (1 << CLOCK_PIN);
    DDRB |= (1 << DATA_PIN);
}

void init_buttons() {
    for (byte i = 0; i < BUTTON_COUNT; i++) {
        Button new_button(i);
        buttons[i] = new_button;
    }
}

void init_leds() {
    for (byte i = 0; i < LEDS_COUNT; i++) {
        DDRB |= (1 << LED_PINS[i]);
        PORTB |= (1 << LED_PINS[i]);
    }
}

void init() {
    serial.init(115200);
    init_pins();
    init_buttons();
    init_leds();
    display.write_number(6767);
}

void decision_tree() {
    switch (lock.state) {
        case LOCKED:
        case MODIFIED:
            display.write_number(lock.current_code);
            break;
        case PASS:
            display.write_string("PASS");
            break;
        case FAIL:
            display.write_string("FAIL");
            break;
        case UNLOCKED:
            display.write_string("    ");
        default:
        break;
    }
}

void loop() { // translate to switches per the lock state later and divide into functions per state / button
    if (buttons[FIRST].is_triggered()) {
        lock.button_1_activity();
    }
    if (buttons[SECOND].is_triggered()) {
        lock.button_2_activity();
    }
    if (buttons[THIRD].is_triggered()) {
        lock.button_3_activity();
    } 
    display.write_number(lock.current_code);
    if (lock.state == LOCKED || lock.state == MODIFIED) {
        display.write_cursor(lock.cursor);
    }
    display.refresh(); // do not remove

}

int main(void) {
    init();
    while (true) {
        loop();
    }
    return 0;
}