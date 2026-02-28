#include "button.hpp"
#include "constants.hpp"
#include "death.hpp"
#include "display.hpp"
#include "light.hpp"
#include "lock.hpp"
#include "states.hpp"
#include "storage.hpp"
// #include "uart.hpp"

enum Mode { GUESS_CODE, SHOW_CODE, RESET_PIN };

constexpr Mode APP_MODE = GUESS_CODE;

Lock lock;
Death death;
Display display;
Light lights[LIGHTS_COUNT];
Button buttons[BUTTON_COUNT];
Storage storage;
// UART serial;

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
    // serial.init(115200);
    init_buttons();
    init_lights();
    init_storage();
    init_lock();
    init_death();
}

void display_decision_tree() {
    switch (lock.state) {
        case LOCKED:
        case MODIFIED:
            display.write_number(lock.current_code);
            display.write_cursor(lock.cursor);
            break;
        case PASS:
            display.write_string(PASS_MESSAGE);
            break;
        case FAIL:
            display.write_string(FAIL_MESSAGE);
            break;
        case LOCK:
            display.write_string(LOCK_MESSAGE);
            break;
        case UNLOCKED:
            display.write_string(UNLOCKED_MESSAGE);
            break;
        case SET:
            display.write_string(SET_MESSAGE);
            break;
        case PASSWORD_OK:
            display.write_string(PASSWORD_OK_MESSAGE);
            break;
        case DEAD:
            display.write_string((const char*)death.current_word);
            display.write_cursor(death.cursor);
        default:
            break;
    }
}

void lock_decision_tree() {
    switch (lock.state) {
        case LOCKED:
            locked_state();
            break;
        case MODIFIED:
            modified_state();
            break;
        case PASS:
            pass_state();
            break;
        case FAIL:
            fail_state();
            break;
        case LOCK:
            lock_state();
            break;
        case UNLOCKED:
            unlocked_state();
            break;
        case SET:
            set_state();
            break;
        case PASSWORD_OK:
            password_ok_state();
            break;
        case DEAD:
            dead_state();
        default:
            break;
    }
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
            lock_decision_tree();
            display_decision_tree();
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