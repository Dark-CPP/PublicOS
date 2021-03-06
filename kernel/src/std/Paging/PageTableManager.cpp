#include "PageTableManager.h"
#include "PageMapIndexer.h"

#include <stdint.h>

#include "PageFrameAllocator.h"
#include "../memory.h"

namespace std
{
    PageTableManager::PageTableManager(PageTable* PML4Address) : PML4(PML4Address)
    {
        ;
    }

    void PageTableManager::MapMemory(void* virtualMemory, void* physicalMemory)
    {
        PageMapIndexer indexer((uint64_t)virtualMemory);
        PageDirectoryEntry PDE;

        PDE = PML4->entries[indexer.PDP_i];
        PageTable* PDP;
        if(!PDE.Present)
        {
            PDP = (PageTable*)GlobalAllocator.RequestPage();
            memset(PDP, 0, 4096);
            PDE.Address = (uint64_t)PDP >> 12;
            PDE.Present = true;
            PDE.ReadWrite = true;
            PML4->entries[indexer.PDP_i] = PDE;
        }
        else
        {
            PDP = (PageTable*)((uint64_t)PDE.Address << 12);
        }

        PDE = PDP->entries[indexer.PD_i];
        PageTable* PD;
        if(!PDE.Present)
        {
            PD = (PageTable*)GlobalAllocator.RequestPage();
            memset(PD, 0, 4096);
            PDE.Address = (uint64_t)PD >> 12;
            PDE.Present = true;
            PDE.ReadWrite = true;
            PDP->entries[indexer.PD_i] = PDE;
        }
        else
        {
            PD = (PageTable*)((uint64_t)PDE.Address << 12);
        }

        PDE = PD->entries[indexer.PD_i];
        PageTable* PT;
        if(!PDE.Present)
        {
            PT = (PageTable*)GlobalAllocator.RequestPage();
            memset(PT, 0, 4096);
            PDE.Address = (uint64_t)PT >> 12;
            PDE.Present = true;
            PDE.ReadWrite = true;
            PD->entries[indexer.PT_i] = PDE;
        }
        else
        {
            PT = (PageTable*)((uint64_t)PDE.Address << 12);
        }

        PDE = PT->entries[indexer.PD_i];
        PDE.Address = (uint64_t)physicalMemory >> 12;
        PDE.Present = true;
        PDE.ReadWrite = true;
        PT->entries[indexer.P_i] = PDE;
    }
    
    PageTableManager::~PageTableManager()
    {
    }
}
