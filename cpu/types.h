#ifndef TYPES_H
#define TYPES_H

typedef unsigned int    u32;
typedef          int    s32;
typedef unsigned short  u16;
typedef          short  s16;
typedef unsigned char   u8;
typedef          char   s8;

#define lo_16(addr) (u16)((addr) & 0xFFFF)
#define hi_16(addr) (u16)(((addr) >> 16) & 0xFFFF)

#endif