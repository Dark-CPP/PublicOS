#pragma once

#include "Paging.h"
#include "../../Console/Console.h"
#include "../cstr.h"

namespace std
{
    class PageTableManager
    {
        public:
            PageTable* PML4;
        public:
            PageTableManager(PageTable* PML4Address);

            void MapMemory(void* virtualMemory, void* physicalMemory);

            ~PageTableManager();
    };
}
