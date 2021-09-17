#include "cstr.h"

char uBuffer[128];
const char* std::to_cstring(uint64_t value)
{
    uint8_t size;
    uint64_t sizeVar = value;
    while (sizeVar / 10 > 0)
    {
        sizeVar /= 10;
        size++;
    }
    
    uint8_t index = 0;

    while (value / 10 > 0)
    {
        uint8_t r = value % 10;
        value /= 10;

        uBuffer[size - index] = r + '0';
        index++;
    }
    uint8_t r = value % 10;
    uBuffer[size - index] = r + '0';
    uBuffer[size + 1] = 0;

    return uBuffer;
}

char iBuffer[128];
const char* std::to_cstring(int64_t value)
{
    uint8_t offset = 0;

    if(value < 0)
    {
        offset += 1;
        value *= -1;
        iBuffer[0] = '-';
    }

    uint8_t size;
    uint64_t sizeVar = value;
    while (sizeVar / 10 > 0)
    {
        sizeVar /= 10;
        size++;
    }
    
    uint8_t index = 0;

    while (value / 10 > 0)
    {
        uint8_t r = value % 10;
        value /= 10;

        iBuffer[size - index + offset] = r + '0';
        index++;
    }
    uint8_t r = value % 10;
    iBuffer[size - index + offset] = r + '0';
    iBuffer[size + offset + 1] = 0;

    return iBuffer;
}

char dBuffer[128];
const char* std::to_cstring(double value, uint8_t decimalPlaces)
{
    if(decimalPlaces > 20) decimalPlaces = 20;

    char* intPtr = (char*)to_cstring((int64_t)value);
    char* doublePtr = dBuffer;

    if(value < 0){ value *= -1; }

    while (*intPtr != 0)
    {
        *doublePtr = *intPtr;
        doublePtr++; intPtr++;
    }

    *doublePtr = '.'; doublePtr++;
    
    double newValue = value - (int)value;

    for(uint8_t i = 0; i < decimalPlaces; i++)
    {
        newValue *= 10;
        *doublePtr = (int)newValue + '0';
        newValue -= (int)newValue;
        doublePtr++;
    }

    *doublePtr = 0;

    return dBuffer;
}

char uhBuffer64[128];
const char* std::to_cstring_hex(uint64_t value)
{
    uint64_t* valPtr = &value;
    uint8_t* ptr;
    uint8_t tmp;
    uint8_t size = 8 * 2 - 1;
    char* Buffer = uhBuffer64;

    for (uint8_t i = 0; i < size; i++){
        ptr = ((uint8_t*)valPtr + i);
        tmp = ((*ptr & 0xF0) >> 4);
        Buffer[size - (i * 2 + 1)] = tmp + (tmp > 9 ? 55 : '0');
        tmp = ((*ptr & 0x0F));
        Buffer[size - (i * 2)] = tmp + (tmp > 9 ? 55 : '0');
    }
    Buffer[size + 1] = 0;
    return Buffer;
}

char uhBuffer32[128];
const char* std::to_cstring_hex(uint32_t value)
{
    uint32_t* valPtr = &value;
    uint8_t* ptr;
    uint8_t tmp;
    uint8_t size = 4 * 2 - 1;
    char* Buffer = uhBuffer32;

    for (uint8_t i = 0; i < size; i++){
        ptr = ((uint8_t*)valPtr + i);
        tmp = ((*ptr & 0xF0) >> 4);
        Buffer[size - (i * 2 + 1)] = tmp + (tmp > 9 ? 55 : '0');
        tmp = ((*ptr & 0x0F));
        Buffer[size - (i * 2)] = tmp + (tmp > 9 ? 55 : '0');
    }
    Buffer[size + 1] = 0;
    return Buffer;
}

char uhBuffer16[128];
const char* std::to_cstring_hex(uint16_t value)
{
    uint16_t* valPtr = &value;
    uint8_t* ptr;
    uint8_t tmp;
    uint8_t size = 2 * 2 - 1;
    char* Buffer = uhBuffer16;

    for (uint8_t i = 0; i < size; i++){
        ptr = ((uint8_t*)valPtr + i);
        tmp = ((*ptr & 0xF0) >> 4);
        Buffer[size - (i * 2 + 1)] = tmp + (tmp > 9 ? 55 : '0');
        tmp = ((*ptr & 0x0F));
        Buffer[size - (i * 2)] = tmp + (tmp > 9 ? 55 : '0');
    }
    Buffer[size + 1] = 0;
    return Buffer;
}

char uhBuffer8[128];
const char* std::to_cstring_hex(uint8_t value)
{
    uint8_t* valPtr = &value;
    uint8_t* ptr;
    uint8_t tmp;
    uint8_t size = 1 * 2 - 1;
    char* Buffer = uhBuffer64;

    for (uint8_t i = 0; i < size; i++){
        ptr = ((uint8_t*)valPtr + i);
        tmp = ((*ptr & 0xF0) >> 4);
        Buffer[size - (i * 2 + 1)] = tmp + (tmp > 9 ? 55 : '0');
        tmp = ((*ptr & 0x0F));
        Buffer[size - (i * 2)] = tmp + (tmp > 9 ? 55 : '0');
    }
    Buffer[size + 1] = 0;
    return Buffer;
}
