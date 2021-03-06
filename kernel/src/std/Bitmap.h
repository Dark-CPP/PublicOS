#pragma once

#include <stdint.h>
#include <stddef.h>

#include "../Console/Console.h"
#include "cstr.h"

namespace std
{
    class Bitmap
    {
        public:
            size_t Size;
            uint8_t* Buffer;

            bool operator[](uint64_t index);
            void Set(uint64_t index, bool value);
    };
    
}