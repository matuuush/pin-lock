#ifndef TEXT_HPP
#define TEXT_HPP

#include "display.hpp"

class Text {
private:
    char text[DISPLAY_POSITIONS];
public:
    void set(char text[]);
    char* get();
};

#endif