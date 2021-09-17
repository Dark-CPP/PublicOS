#pragma once

#include <stdint.h>

namespace GL
{
    class Color
    {
        public:
            uint8_t r;
            uint8_t g;
            uint8_t b;
            uint8_t a;

            Color() { ; }
            Color(uint8_t red, uint8_t green, uint8_t blue, uint8_t alpha = 255) : r(red), g(green), b(blue), a(alpha) { ; }

            unsigned int to_UINT32();

    };

    class vec2
    {
        public:
            float x;
            float y;

            vec2() : x(0.0f), y(0.0f) {;}
            vec2(float s) : x(s), y(s) {;}
            vec2(float _x, float _y) : x(_x), y(_y) {;}

            vec2 operator +(vec2 left)
            {
                return vec2(x + left.x, y + left.y);
            }

            vec2 operator -(vec2 left)
            {
                return vec2(x - left.x, y - left.y);
            }

            vec2 operator *(float left)
            {
                return vec2(x * left, y * left);
            }

            vec2 operator /(float left)
            {
                return vec2(x / left, y / left);
            }

            ~vec2(){;}
    };

    class vec2u
    {
        public:
            unsigned int x;
            unsigned int y;

            vec2u(){;}
            vec2u(unsigned int _x, unsigned int _y) : x(_x), y(_y) {;}

            vec2u operator +(vec2u left)
            {
                return vec2u(x + left.x, y + left.y);
            }

            vec2u operator -(vec2 left)
            {
                return vec2u(x - left.x, y - left.y);
            }

            vec2u operator *(unsigned int left)
            {
                return vec2u(x * left, y * left);
            }

            ~vec2u(){;}
    };
}
