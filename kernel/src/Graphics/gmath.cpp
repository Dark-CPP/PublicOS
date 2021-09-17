#include "gmath.h"

namespace GL
{
    unsigned int Color::to_UINT32()
    {
        unsigned int _color = 0;

        // BGRA, reversed, ARGB
        _color += (0x01000000) * a;
        _color += (0x00010000) * r;
        _color += (0x00000100) * g;
        _color += (0x00000001) * b;

        return _color;
    }
}

