#include "constants.hpp"

word power_function(byte base, byte exponent) {
    word result = 1;
    while (exponent-- > 0) {
        result *= base;
    }
    return result;
}