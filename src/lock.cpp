#include "lock.hpp"

#include "display.hpp"

void Lock:: increment_digit() {
    byte exponent = DIGITS_COUNT - cursor - 1;
    word increment = power_function(10, exponent);
    current_code += increment;
    current_code %= OVERFLOW;
}

void Lock::move_cursor() {
    ++cursor %= DIGITS_COUNT;
}

void Lock::unlock_attempt() {
    state = (current_code == pin_code) ? PASS : FAIL;
}

void Lock::hide_message() {
    if (state == PASS) {
        state = UNLOCKED;
    } else if (state == FAIL) {
        state = LOCKED;
    }
}

void Lock::button_1_activity() {
    switch (state) {
        case LOCKED:
        case MODIFIED:
            increment_digit();
            break;
        case PASS:
        case FAIL:
            hide_message();
            break;
        case UNLOCKED:
        default:
            break;
    }
}

void Lock::button_2_activity() {
    switch (state) {
        case LOCKED:
        case MODIFIED:
            move_cursor();
            break;
        case PASS:
        case FAIL:
            hide_message();
        case UNLOCKED:
        default:
            break;
    }
}

void Lock::button_3_activity() {
    switch (state) {
        case LOCKED:
            unlock_attempt();
            break;
        case UNLOCKED:
            new_pin_code_procedure();
            break;
        case MODIFIED:
            set_new_pin_code();
            break;
        case PASS:
        case FAIL:
            hide_message();
        default:
            break;
    }
}

void Lock::new_pin_code_procedure() {
    state = MODIFIED;
}

void Lock::lock_system() {
    state = LOCKED;
}
void Lock::set_new_pin_code() {
    pin_code = current_code;
    current_code = 0;
}