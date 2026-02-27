#ifndef LOCK_HPP
#define LOCK_HPP

#include "constants.hpp"
#include "display.hpp"

static word OVERFLOW = power_function(10, DIGITS_COUNT);

enum LockState { LOCKED, LOCK, UNLOCKED, PASS, FAIL, SET, PASSWORD_OK, MODIFIED };

class Lock {
private:
    void locked_increment();
public:
    word pin_code;
    word current_code;
    byte cursor = 0;
    LockState state = LOCKED;
    void set_current_code(word number);
    void hide_message();
    void increment_digit();
    void move_cursor();
    void unlock_attempt();
    void lock_system();
    void change_pin_beginning();
    void change_pin_during();
    void change_pin_after();
};

#endif