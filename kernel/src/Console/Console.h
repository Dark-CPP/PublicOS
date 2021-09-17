#pragma once

#include "../math.h"
#include "../SimpleFonts.h"
#include "../Graphics/GL.h"

class Console
{
    private:
        GL::RenderBuffer* renderbuffer;
        PSF1_FONT* PSF1_Font;
        Point CursorPosition;
        GL::Color color;

    public:
        void Init(GL::RenderBuffer& rb, PSF1_FONT* psf1_font);

        void CursorToPos(Point newPosition) { CursorPosition = { newPosition.x * 8, newPosition.y * 16 }; }

        void nextline() { CursorPosition = { 0, CursorPosition.y + 16 }; }

        void SetColor(GL::Color _color) { color = _color;}

        void PutChar(char chr, unsigned int xoffset, unsigned int yoffset);

        void Print(const char* str);
};

extern Console console;
