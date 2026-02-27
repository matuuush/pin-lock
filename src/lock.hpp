#ifndef LOCK_HPP
#define LOCK_HPP

#include "constants.hpp"
#include "display.hpp"

static word OVERFLOW = power_function(10, DIGITS_COUNT);

enum LockState { LOCKED, UNLOCKED, PASS, FAIL, MODIFIED };

class Lock {
private:
    void locked_increment();
public:
    word pin_code;
    word current_code = 0;
    byte cursor = 0;
    LockState state = LOCKED;
    void button_1_activity();
    void button_2_activity();
    void button_3_activity();

    void hide_message();
    void increment_digit();
    void move_cursor();
    void unlock_attempt();
    void lock_system();
    void new_pin_code_procedure();
    void set_new_pin_code();
};

#endif