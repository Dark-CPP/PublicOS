#pragma once

#include <stdint.h>

namespace std
{
    class PageMapIndexer
    {
        public:
            uint64_t PDP_i;
            uint64_t PD_i;
            uint64_t PT_i;
            uint64_t P_i;

        public:
            PageMapIndexer(uint64_t virtualAddress);
            ~PageMapIndexer();
    };
    
    
    
}
