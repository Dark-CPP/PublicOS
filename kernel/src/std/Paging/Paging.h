#pragma once

#include <stdint.h>

namespace std
{
    struct PageDirectoryEntry
    {
        bool Present : 1;
        bool ReadWrite : 1;
        bool UserSuper : 1;
        bool WriteThrough : 1;
        bool CacheDisabled : 1;
        bool Accessed : 1;
        bool ignore0 : 1;
        bool LargerPages : 1;
        bool ignore1 : 1;
        uint8_t Available = 3;
        uint64_t Address = 52;
    };

    struct PageTable
    {
        PageDirectoryEntry entries[512];
    } __attribute__((aligned(0x1000)));
    
    
}
