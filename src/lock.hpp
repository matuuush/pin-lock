#ifndef LOCK_HPP
#define LOCK_HPP

#include "constants.hpp"
#include "display.hpp"

constexpr byte DEFAULT_ATTEMPTS = 3;

static word OVERFLOW = power_function(NUMERAL_BASIS, DIGITS_COUNT);

enum LockState { LOCKED, LOCK, FREE, PASS, FAIL, SET, GOOD, MODIFIED, DEAD };

class Lock {
public:
    word pin_code;
    word current_code;
    byte cursor;
    byte attempts;
    LockState state;
    Lock();
    Lock(word pin);
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