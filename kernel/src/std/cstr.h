#pragma once

#include <stdint.h>

namespace std
{
    const char* to_cstring(uint64_t value);
    const char* to_cstring(int64_t value);
    const char* to_cstring(double value, uint8_t decimalPlaces = 2);

    const char* to_cstring_hex(uint64_t value);
    const char* to_cstring_hex(uint32_t value);
    const char* to_cstring_hex(uint16_t value);
    const char* to_cstring_hex(uint8_t value);
}
