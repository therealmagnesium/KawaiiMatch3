#pragma once
#include <stdint.h>
#include <stdlib.h>

typedef int8_t s8;
typedef int16_t s16;
typedef int32_t s32;
typedef uint8_t u8;
typedef uint16_t u16;
typedef uint32_t u32;

struct WindowData
{
    u32 width;
    u32 height;
    const char* title;
};
