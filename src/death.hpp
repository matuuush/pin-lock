#ifndef DEATH_HPP
#define DEATH_HPP

#include "constants.hpp"
#include "display.hpp"

class Death {
public:
    byte current_word[DIGITS_COUNT];
    byte wanted_word[DIGITS_COUNT];
    byte cursor;
    Death();
    Death(const char* current, const char* wanted);
    void increment_char();
    void move_cursor();
    void unlock_attempt();
};

#endif