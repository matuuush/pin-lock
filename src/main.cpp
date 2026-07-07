#include "button.hpp"
#include "concrete_states.hpp"
#include "constants.hpp"
#include "death.hpp"
#include "display.hpp"
#include "light.hpp"
#include "lock.hpp"
#include "storage.hpp"

// #define DEBUG

#ifdef DEBUG
#include "uart.hpp"
#endif

enum Mode { GUESS_CODE, SHOW_CODE, RESET_PIN };

constexpr Mode APP_MODE = GUESS_CODE;

Lock lock;
Death death;
Display display;
Light lights[LIGHTS_COUNT];
Button buttons[BUTTON_COUNT];
Storage storage;

#ifdef DEBUG
UART serial;
#endif

void init_buttons() {
    for (byte i = 0; i < BUTTON_COUNT; i++) {
        Button new_button(i);
        buttons[i] = new_button;
    }
}

void init_lights() {
    for (byte i = 0; i < LIGHTS_COUNT; i++) {
        Light new_light(i);
        lights[i] = new_light;
    }
}

void init_storage() {
    word saved_pin = storage.read_pin();
    lock.pin_code = saved_pin;
}

void init_lock() {
    word number = (APP_MODE == SHOW_CODE) ? lock.pin_code : DEFAULT_CODE;
    lock.set_current_code(number);
}

void init_death() {
    Death new_death(DEAD_MESSAGE, LOCK_MESSAGE);
    death = new_death;
}

void init() {
#ifdef DEBUG
    serial.init(115200);
#endif
    init_buttons();
    init_lights();
    init_storage();
    init_lock();
    init_death();
}

bool loop() {
    switch (APP_MODE) {
        case SHOW_CODE:
            display.write_number(lock.pin_code);
            break;
        case RESET_PIN:
            storage.write_pin(0);
            return false;
        case GUESS_CODE:
        default:
            lock.state->lock_action();
            lock.state->display_action();
            turn_off_lights();
            _delay_ms(1);
            break;
    }
    display.refresh();
    return true;
}

int main(void) {
    init();
    while (loop());
    return 0;
}
