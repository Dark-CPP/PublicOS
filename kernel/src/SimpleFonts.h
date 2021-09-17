#pragma once

struct PSF1_HEADER
{
	unsigned char magic[2];
	unsigned char mode;
	unsigned char charsize;
};

struct PSF1_FONT
{
	PSF1_HEADER* pfs1_header;
	void* GlyphBuffer;
};

