#include "PageFrameAllocator.h"

namespace std
{
    uint64_t freeMemory;
    uint64_t reservedMemory;
    uint64_t usedMemory;
    bool Initialised = false;

    PageFrameAllocator GlobalAllocator;

    void PageFrameAllocator::InitBitmap(size_t bitmap_size, void* bufferaddress)
    {
        PageBitmap.Size = bitmap_size;
        PageBitmap.Buffer = (uint8_t*)bufferaddress;

        for(int i = 0; i < bitmap_size; i++)
        {
            *(uint8_t*)(PageBitmap.Buffer + i) = 0;
        }
    }

    void PageFrameAllocator::UnreservePage(void* address)
    {
        uint64_t index = (uint64_t)address / 4096;
        if(PageBitmap[index] == false) return;
        PageBitmap.Set(index, false);
        freeMemory += 4096;
        reservedMemory -= 4096;
    }

    void PageFrameAllocator::UnreservePages(void* address, uint8_t pageCount)
    {
        for(unsigned int t = 0; t < pageCount; t++)
        {
            UnreservePage((void*)((uint64_t)address + (t * 4096)));
        }
    }

    void PageFrameAllocator::ReservePage(void* address)
    {
        uint64_t index = (uint64_t)address / 4096;
        if(PageBitmap[index] == true) return;
        PageBitmap.Set(index, true);
        freeMemory -= 4096;
        reservedMemory += 4096;
    }

    void PageFrameAllocator::ReservePages(void* address, uint8_t pageCount)
    {
        for(unsigned int t = 0; t < pageCount; t++)
        {
            ReservePage((void*)((uint64_t)address + (t * 4096)));
        }
    }

    void PageFrameAllocator::FreePage(void* address)
    {
        uint64_t index = (uint64_t)address / 4096;
        if(PageBitmap[index] == false) return;
        PageBitmap.Set(index, false);
        freeMemory += 4096;
        usedMemory -= 4096;
    }

    void PageFrameAllocator::FreePages(void* address, uint8_t pageCount)
    {
        for(unsigned int t = 0; t < pageCount; t++)
        {
            FreePage((void*)((uint64_t)address + (t * 4096)));
        }
    }

    void PageFrameAllocator::LockPage(void* address)
    {
        uint64_t index = (uint64_t)address / 4096;
        if(PageBitmap[index] == true) return;
        PageBitmap.Set(index, true);
        freeMemory -= 4096;
        usedMemory += 4096;
    }

    void PageFrameAllocator::LockPages(void* address, uint8_t pageCount)
    {
        for(unsigned int t = 0; t < pageCount; t++)
        {
            LockPage((void*)((uint64_t)address + (t * 4096)));
        }
    }

    void PageFrameAllocator::ReadEFIMemoryMap(EFI_MEMORY_DESCRIPTOR* mMap, size_t mMapSize, size_t mMapDescSize)
    {
        if(Initialised) return;
        Initialised = true;

        uint64_t mMapEntries = mMapSize / mMapDescSize;

        void* LargestFreeMemSeg = NULL;
        size_t LargestFreeMemSegSize = 0;

        for(unsigned int i = 0; i < mMapEntries; i++)
        {
            EFI_MEMORY_DESCRIPTOR* desc = (EFI_MEMORY_DESCRIPTOR*)((uint64_t)mMap + (i * mMapDescSize));
            if(desc->type == 7) // type == "EfiConventionalMemory"
            {
                if(desc->numPages * 4096 > LargestFreeMemSegSize)
                {
                    LargestFreeMemSeg = desc->physAddr;
                    LargestFreeMemSegSize = desc->numPages * 4096;
                }
            }
        }

        uint64_t MemorySize = GetMemorySize(mMap, mMapEntries, mMapDescSize);
        freeMemory = MemorySize;
        uint64_t bitmapsize = MemorySize / (4096 * 8) + 1;

        //initialize bitmap
        InitBitmap(bitmapsize, LargestFreeMemSeg);

        LockPages(&PageBitmap, PageBitmap.Size / 4096 + 1);

        for(unsigned int i = 0; i < mMapEntries; i++)
        {
            EFI_MEMORY_DESCRIPTOR* desc = (EFI_MEMORY_DESCRIPTOR*)((uint64_t)mMap + (i * mMapDescSize));
            if(desc->type != 7) // type != "EfiConventionalMemory"
            {
                ReservePages(desc->physAddr, desc->numPages);
            }
        }
    }

    void* PageFrameAllocator::RequestPage()
    {
        for(uint64_t index = 0; index < PageBitmap.Size * 8; index++)
        {
            if(PageBitmap[index] == true) continue;

            LockPage((void*)(index * 4096));
            return (void*)(index * 4096);
        }

        return NULL; // TODO: Page Frame Swap to File
    }

    uint64_t PageFrameAllocator::GetFreeRAM()
    {
        return freeMemory;
    }
    uint64_t PageFrameAllocator::GetUsedRAM()
    {
        return usedMemory;
    }
    uint64_t PageFrameAllocator::GetReservedRAM()
    {
        return reservedMemory;
    }
}
