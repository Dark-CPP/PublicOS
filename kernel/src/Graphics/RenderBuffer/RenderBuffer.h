#pragma once

#include "../FrameBuffer.h"
#include "../gmath.h"

namespace GL
{
    class RenderBuffer
    {
        private:
            FrameBuffer* frameBuffer;
            unsigned int* Pixels;
        public:
            RenderBuffer(FrameBuffer* fbuffer = nullptr) : frameBuffer(fbuffer) { if(fbuffer){ Pixels = (unsigned int*)fbuffer->BaseAddress; } }

            void clear(Color color = Color(0, 0, 0));

            void SetPixel(Color color, vec2u Position);

            void SetPixelFloat(Color color, vec2 Position);

            vec2u Size();

            void DrawLineTest();

            ~RenderBuffer(){ ; }
    };    
}
