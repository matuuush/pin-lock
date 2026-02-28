#ifndef STATES_HPP
#define STATES_HPP

#include "button.hpp"
#include "constants.hpp"
#include "light.hpp"
#include "lock.hpp"
#include "storage.hpp"

extern Lock lock;
extern Light lights[LIGHTS_COUNT];
extern Button buttons[BUTTON_COUNT];
extern Storage storage;

void show_remaining_attempts_count() {
    for (byte i = 0; i < LIGHTS_COUNT; i++) {
        Light light = lights[i];
        bool status = light.index < lock.attempts;
        lights[i].change(status);
    }
}

void locked_state() {
    if (buttons[FIRST].is_triggered()) {
        lock.increment_digit();
    }
    if (buttons[SECOND].is_triggered()) {
        lock.move_cursor();
    }
    if (buttons[THIRD].is_triggered()) {
        lock.unlock_attempt();
    }
    show_remaining_attempts_count();
}

void modified_state() {
    if (buttons[FIRST].is_triggered()) {
        lock.increment_digit();
    }
    if (buttons[SECOND].is_triggered()) {
        lock.move_cursor();
    }
    if (buttons[THIRD].is_triggered()) {
        lock.change_pin_after();
        word new_pin = lock.pin_code;
        storage.write_pin(new_pin);
    }
}

void pass_state() {
    if (buttons[FIRST].is_triggered()) {
        lock.change_pin_beginning();
    }
    if (buttons[SECOND].is_triggered()
    || buttons[THIRD].is_triggered()) {
        lock.hide_message();
    }
}

void fail_state() {
    if (buttons[FIRST].is_triggered()
    || buttons[SECOND].is_triggered()
    || buttons[THIRD].is_triggered()) {
        lock.hide_message();
    }
    show_remaining_attempts_count();
}

void lock_state() {
    if (buttons[FIRST].is_triggered()
    || buttons[SECOND].is_triggered()
    || buttons[THIRD].is_triggered()) {
        lock.set_current_code(DEFAULT_CODE);
        lock.hide_message();
    }
    show_remaining_attempts_count();
}

void unlocked_state() {
    if (buttons[FIRST].is_triggered()) {
        // do nothing
    }
    if (buttons[SECOND].is_triggered()) {
        lock.lock_system();
    }
    if (buttons[THIRD].is_triggered()) {
        lock.change_pin_beginning();
    }
}

void set_state() {
    if (buttons[FIRST].is_triggered()
    || buttons[SECOND].is_triggered()
    || buttons[THIRD].is_triggered()) {
        lock.change_pin_during();
    }
}

void password_ok_state() {
    if (buttons[FIRST].is_triggered()
    || buttons[SECOND].is_triggered()
    || buttons[THIRD].is_triggered()) {
        lock.hide_message();
    }
}

#endif