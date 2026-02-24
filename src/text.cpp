#include "text.hpp"

void Text::set(char str[]) {
    for (byte i = 0; i < DIGITS_COUNT; i++){
        char ch = str[i];
        text[i] = ((ch == '\0') ? ' ' : ch);
    }
}

char* Text::get() {
    return text;
}