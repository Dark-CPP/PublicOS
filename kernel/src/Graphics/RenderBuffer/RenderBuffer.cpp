#include "RenderBuffer.h"

namespace GL
{
    void RenderBuffer::clear(Color color)
    {
        for(unsigned int y = 0; y < frameBuffer->height; y++)
        {
            for(unsigned int x = 0; x < frameBuffer->PixelsPerScanLine; x++)
            {
                *(unsigned int*)(Pixels + x + (y * frameBuffer->PixelsPerScanLine)) = color.to_UINT32();
            }
        }
    }

    void RenderBuffer::SetPixel(Color color, vec2u Position)
    {
        *(unsigned int*)(Pixels + Position.x + (Position.y * frameBuffer->PixelsPerScanLine)) = color.to_UINT32();
    }

    void RenderBuffer::SetPixelFloat(Color color, vec2 Position)
    {
        vec2 MidPos = (Position + vec2(1.0f)) / 2.0f;
        vec2u Pos = { Position.x * frameBuffer->width, Position.y * frameBuffer->height };

        SetPixel(color, Pos);
    }

    void RenderBuffer::DrawLineTest()
    {
        Color White(255, 0, 0);

        for(unsigned int y = 100; y < 150; y++)
        {
            for(unsigned int x = 0; x < frameBuffer->width; x++)
            {
                SetPixel(White, {x, y});
            }
        }
    }

    vec2u RenderBuffer::Size()
    {
        return vec2u{ frameBuffer->width, frameBuffer->height };
    }
}
