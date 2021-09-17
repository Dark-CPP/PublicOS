#include "Console.h"

Console console;

void Console::Init(GL::RenderBuffer& framebuffer, PSF1_FONT* psf1_font)
{
    renderbuffer = &framebuffer;
    PSF1_Font = psf1_font;

    CursorPosition = {0, 0};
    color = GL::Color(255, 255, 255);
}

void Console::PutChar(char chr, unsigned int xoffset, unsigned int yoffset)
{
  char* fontPtr = (char*)PSF1_Font->GlyphBuffer + (chr * PSF1_Font->pfs1_header->charsize);

  for(unsigned int y = yoffset; y < yoffset + 16; y++)
  {
    for(unsigned int x = xoffset; x < xoffset + 8; x++)
    {
      if((*fontPtr & (0b10000000 >> (x - xoffset))) > 0)
      {
        renderbuffer->SetPixel(color, {x, y});
      }
    }

    fontPtr++;
  }

}

void Console::Print(const char* str)
{
  char* chr = (char*)str;

  while (*chr != 0)
  {
    PutChar(*chr, CursorPosition.x, CursorPosition.y);
    CursorPosition.x += 8;
    if(CursorPosition.x > renderbuffer->Size().x)
    {
      CursorPosition.x = 0;
      CursorPosition.y += 16;
    }
    chr++;
  }
}
