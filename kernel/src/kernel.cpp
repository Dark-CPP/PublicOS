#include <stddef.h>
#include "Console/Console.h"
#include "std/std.h"
#include "Graphics/GL.h"
#include "efiMemory.h"

void * __gxx_personality_v0 = 0;
void * _Unwind_Resume = 0;

struct BootInfo
{
	FrameBuffer* framebuffer;
	PSF1_FONT* psf1_font;
	EFI_MEMORY_DESCRIPTOR* mMap;
	uint64_t mMapSize;
	uint64_t mMapDescSize;
};

extern uint64_t _KernelStart;
extern uint64_t _KernelEnd;

extern "C" void _start(BootInfo* bootInfo)
{
  GL::RenderBuffer rb(bootInfo->framebuffer);

  console.Init(rb, bootInfo->psf1_font);

  rb.clear();

  uint64_t mMapEntries = bootInfo->mMapSize / bootInfo->mMapDescSize;

  std::GlobalAllocator = std::PageFrameAllocator();

  std::GlobalAllocator.ReadEFIMemoryMap(bootInfo->mMap, bootInfo->mMapSize, bootInfo->mMapDescSize);

  uint64_t KernelSize = (uint64_t)&_KernelEnd - (uint64_t)&_KernelStart;

  uint64_t KernelPages = KernelSize / 4096 + 1;

  std::GlobalAllocator.LockPages(&_KernelStart, KernelPages);

  console.Print("Creating PLM4!");
  console.nextline();

  std::PageTable* PLM4 = (std::PageTable*)std::GlobalAllocator.RequestPage();
  std::memset(PLM4, 0, 0x1000);

  std::PageTableManager pageTableManager(PLM4);

  console.Print("New PageMap Creating!");
  console.nextline();

  for (uint64_t i = 0; i < std::GetMemorySize(bootInfo->mMap, mMapEntries, bootInfo->mMapDescSize); i += 0x1000)
  {
    pageTableManager.MapMemory((void*)i, (void*)i);
  }

  console.Print("New PageMap Creating - Part 1 Done!");
  console.nextline();

  uint64_t fbbase = (uint64_t)bootInfo->framebuffer->BaseAddress;
  uint64_t fbsize = (uint64_t)bootInfo->framebuffer->BufferSize + 0x1000;

  for(uint64_t i = fbbase; i < fbbase + fbsize; i += 4096)
  {
    pageTableManager.MapMemory((void*)i, (void*)i);
  }

  console.Print("New PageMap Creating - Part 2 Done!");
  console.nextline();

  asm ("mov %0, %%cr3" : : "r" (PLM4));

  console.Print("New PageMap Created!");
}
