#pragma once
#include <stddef.h>

struct FrameBuffer
{
	void* BaseAddress;
	size_t BufferSize;
	unsigned int width;
	unsigned int height;
	unsigned int PixelsPerScanLine;
};
