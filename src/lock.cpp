#include "lock.hpp"

void Lock::set_current_code(word number) {
    current_code = (number % OVERFLOW);
}

void Lock:: increment_digit() {
    byte exponent = DIGITS_COUNT - cursor - 1;
    word increment = power_function(NUMERAL_BASIS, exponent);
    byte prev_digit = (current_code / increment) % NUMERAL_BASIS;
    current_code += increment;
    if (prev_digit == NUMERAL_BASIS - 1) {
        current_code -= NUMERAL_BASIS * increment;
    }
}

void Lock::move_cursor() {
    ++cursor %= DIGITS_COUNT;
}

void Lock::unlock_attempt() {
    if (current_code == pin_code) {
        state = PASS;
        attempts = DEFAULT_ATTEMPTS;
    } else {
        state = FAIL;
        if (attempts > 0) {
            attempts--;
        } else {
            state = DEAD;
        }
    }
}

void Lock::hide_message() {
    if (state == PASS || state == PASSWORD_OK) {
        state = UNLOCKED;
    } else if (state == FAIL || state == LOCK) {
        state = LOCKED;
    }
}

void Lock::change_pin_beginning() {
    state = SET;
}

void Lock::change_pin_during() {
    state = MODIFIED;
}

void Lock::change_pin_after() {
    pin_code = current_code;
    current_code = DEFAULT_CODE;
    state = PASSWORD_OK;
}

void Lock::lock_system() {
    state = LOCK;
}
