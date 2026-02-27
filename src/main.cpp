#include "button.hpp"
#include "constants.hpp"
#include "display.hpp"
#include "lock.hpp"
#include "states.hpp"
#include "storage.hpp"
// #include "uart.hpp"

enum Mode { GUESS_CODE, SHOW_CODE };

constexpr Mode APP_MODE = GUESS_CODE;

constexpr const char* PASS_MESSAGE = "PASS";
constexpr const char* FAIL_MESSAGE = "FAIL";
constexpr const char* LOCK_MESSAGE = "LOCK";
constexpr const char* UNLOCKED_MESSAGE = "FREE";
constexpr const char* SET_MESSAGE = "SET ";
constexpr const char* PASSWORD_OK_MESSAGE = "GOOD";
constexpr const char* EMPTY_MESSAGE = "    ";

Lock lock;
Display display;
Button buttons[BUTTON_COUNT];
Storage storage;
// UART serial;

word index = 0;

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

void init_storage() {
    word saved_pin = storage.read_pin();
    lock.pin_code = saved_pin;
}

void init_lock() {
    word number = (APP_MODE == SHOW_CODE) ? lock.pin_code : 0;
    lock.set_current_code(number);
}

void init() {
    // serial.init(115200);
    init_buttons();
    init_leds();
    init_storage();
    init_lock();
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
        default:
            break;
    }
}

void loop() {
    // operate_lock_with_buttons();
    lock_decision_tree();
    display_decision_tree();
    display.refresh();
}

int main(void) {
    init();
    while (true) {
        loop();
    }
    return 0;
}