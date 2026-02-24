#include "button.hpp"
#include "constants.hpp"
#include "display.hpp"
#include "lock.hpp"

Lock lock;
Display display;
Button buttons[BUTTON_COUNT];

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

void init() {
    init_pins();
    init_buttons();
    display.write_number(0);
}

void loop() {
    if (buttons[FIRST].is_triggered()) {
        display.write_number(index);
        index += 1111;
        //lock.button_1_activity();
    } else if (buttons[SECOND].is_triggered()) {
        display.write_number(index);
        index -= 1111;
        //lock.button_2_activity();
    } else if (buttons[THIRD].is_triggered()) {
        lock.button_3_activity();
    }
    display.refresh();
}

int main(void) {
    init();
    while (true) {
        loop();
    }
    return 0;
}