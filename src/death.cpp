#include "death.hpp"

#include "lock.hpp"

extern Lock lock;
extern void init_death();

Death::Death() { }

Death::Death(const char* current, const char* wanted) : cursor(0) {
    for (byte i = 0; i < DIGITS_COUNT; i++) {
        current_word[i] = current[i];
        wanted_word[i] = wanted[i];
    }
}

void Death::increment_char() {
    char ch = current_word[cursor];
    ++ch;
    ch -= 'A';
    ch %= ALPHABET_SIZE;
    ch += 'A';
    current_word[cursor] = ch;
}

void Death::move_cursor() {
    ++cursor %= DIGITS_COUNT;
}

void Death::unlock_attempt() {
    bool end = false;
    for (byte i = 0; i < DIGITS_COUNT; i++) {
        if (current_word[i] != wanted_word[i]) {
            end = true;
        }
    }
    if (end) {
        init_death();
    } else {
        Lock new_lock(lock.pin_code);
        lock = new_lock;
    }
}