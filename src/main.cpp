#include <avr/io.h>
#include <util/delay.h>

#include "button.hpp"
#include "display.hpp"
#include "constants.hpp"

Display display(1234);
Button buttons[BUTTON_COUNT];
int index = 0;

void init() {
    for (int i = 0; i < BUTTON_COUNT; i++) {
        Button new_button(i);
        buttons[i] = new_button;
    }
}

void loop() {
    display.write_number(index++);
    display.refresh();
    _delay_ms(1); 
}

int main(void) {
    init();
    while (true) {
        loop();
    }
    return 0;
}