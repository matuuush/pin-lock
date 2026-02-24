#include "text.hpp"

void Text::set(char str[]) {
    for (int i = 0; i < DISPLAY_POSITIONS; i++){
        char ch = str[i];
        text[i] = ((ch == '\0') ? ' ' : ch);
    }
}

char* Text::get() {
    return text;
}