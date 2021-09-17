#pragma once

#include "../../efiMemory.h"
#include <stdint.h>
#include "../Bitmap.h"
#include "../memory.h"
#include "../../Console/Console.h"
#include "../cstr.h"

namespace std
{
    class PageFrameAllocator
    {
        private:
            void InitBitmap(size_t bitmap_size, void* bufferaddress);

            void ReservePage(void* address);
            void ReservePages(void* address, uint8_t pageCount);
            void UnreservePage(void* address);
            void UnreservePages(void* address, uint8_t pageCount);
        public:
            Bitmap PageBitmap;

            void ReadEFIMemoryMap(EFI_MEMORY_DESCRIPTOR* mMap, size_t mMapSize, size_t mMapDescSize);

            void FreePage(void* address);
            void FreePages(void* address, uint8_t pageCount);
            void LockPage(void* address);
            void LockPages(void* address, uint8_t pageCount);

            void* RequestPage();

            uint64_t GetFreeRAM();
            uint64_t GetUsedRAM();
            uint64_t GetReservedRAM();
    };

    extern PageFrameAllocator GlobalAllocator;
}
