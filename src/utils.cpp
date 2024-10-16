#include "utils.h"

unsigned long long bitsToNumber(const char* bits, int size) {
    unsigned long long result = 0;
    for (int i = 0; i < size; i++) {
        if (bits[i] == '1') {
            result |= 1ULL << (size - 1 - i);
        }
    }
    return result;
}

