#ifndef MAIN_H
# define MAIN_H

#include "SPIKE.h"

static const __flash byte GLYPHS[] = {
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
    0xfc, 0xfa, 0xf5, 0x0b, 0xe5, 0x6b, 0xe5, 0xcb, 
    0xe5, 0xcb, 0xe5, 0xcb, 0xe5, 0xcb, 0xa5, 0xcb, 
    0xa5, 0x4b, 0xa5, 0x0b, 0x55, 0xab, 0x55, 0xfe, 
    0xef, 0xef, 0xc6, 0x00, 0x55, 0xaa, 0x55, 0xff, 
    0xff, 0xff, 0xff, 0x00, 0xff, 0xdf, 0xf6, 0xff, 
    0xff, 0xfb, 0xdd, 0xff, 0xfb, 0xff, 0xef, 0xff, 
    0xff, 0xff, 0xaa, 0x00, 0x55, 0xaa, 0x55, 0xff, 
    0xff, 0xff, 0xff, 0x00, 0xc7, 0xeb, 0xef, 0xcf, 
    0x3f, 0x5f, 0xaf, 0xd0, 0xef, 0xef, 0xee, 0xef, 
    0xef, 0xef, 0xed, 0xeb, 0xef, 0xed, 0xef, 0xef, 
    0xef, 0xef, 0xee, 0xe0, 0xd5, 0xaa, 0x55, 0x3f, 
    0xe7, 0xed, 0xe7, 0xe0, 0xe7, 0xef, 0xeb, 0xef, 
    0xe5, 0xeb, 0xc5, 0x0b, 0xc5, 0xeb, 0xa5, 0xcb, 
    0xbd, 0x42, 0xa5, 0xa5, 0xa5, 0xa5, 0x42, 0xbd, 
    0xbd, 0x42, 0x99, 0xa5, 0xa5, 0x99, 0x42, 0xff, 
    
    0x00, 0x00, 0x18, 0x3c, 0x3c, 0x18, 0x00, 0x00, // HUD Health (16)
    0x00, 0x18, 0x3c, 0x78, 0x78, 0x3c, 0x18, 0x00, // HUD Lives
    0x00, 0x00, 0x34, 0x24, 0x24, 0x34, 0x00, 0x00, // HUD Ammo
    0x00, 0x08, 0x14, 0x08, 0x08, 0x18, 0x00, 0x00, // HUD Keys
    
    0xff, 0x76, 0x14, 0x14, 0x14, 0x14, 0x1c, 0x08,  // Door Left Closed
    0x08, 0x1c, 0x14, 0x14, 0x14, 0x14, 0x76, 0xff,  // Door Right Closed
    0xff, 0x14, 0x08, 0x00, 0x00, 0x00, 0x00, 0x00,  // Door Left  Open
    0x00, 0x00, 0x00, 0x00, 0x00, 0x08, 0x14, 0xff,  // Door Right Open
    
    0x00, 0x00, 0x00, 0x00, 0x03, 0x06, 0x18, 0x7d,  // Player Idle Up TL
    0x09, 0x04, 0x06, 0x03, 0x01, 0x00, 0x00, 0x00,  // Player Idle Up TR
    0x00, 0x00, 0x60, 0xf0, 0x18, 0x6c, 0xb4, 0x78,  // Player Idle Up BL
    0x78, 0xb4, 0x6c, 0x18, 0x70, 0xe0, 0x00, 0x00,  // Player Idle Up BR
};

#define HUD_HEALTH 16*8
#define HUD_LIVES 17*8
#define HUD_AMMO 18*8
#define HUD_KEYS 19*8

static const __flash Map LEVEL_1 = {
        .cols = 20,
        .rows = 35,
        .tiles = {
      1,   2,   2,   2,   2,   2,   2,   0,   0,   2,   2,   2,   2,   2,   2,   2,   2,   2,   2,   3,
      5,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   7,
      5,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   7,
      5,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   7,
      5,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   1,   2,   2,   2,   2,   2,   2,   2,   4,
      5,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   5,  15,   6,   6,   6,  14,   6,   6,   7,
      5,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   5,   6,  14,   6,   6,   6,   6,   6,   7,
      5,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   9,  10,  10,  10,  10,  10,  10,  10,   4,
      5,   0,   0,   0,   0,   0,   0,   1,   2,   2,   3,   0,   0,   0,   0,   0,   0,   0,   0,   7,
      5,   0,   0,   0,   0,   0,   0,   5,   6,   6,   7,   0,   0,   0,   0,   0,   0,   0,   0,   7,
      5,   0,   0,   0,   0,   0,   0,   5,  14,   6,   7,   0,   0,   0,   0,   0,   0,   0,   0,   7,
      5,   0,   0,   0,   0,   0,   0,   5,   6,  15,   7,   0,   0,   0,   0,   0,   0,   0,   0,   7,
      5,   0,   0,   0,   0,   0,   0,   9,  10,  10,  11,   0,   0,   0,   0,   0,   0,   0,   0,   7,
      5,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   7,
      5,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   7,
      8,   2,   3,   0,   0,   0,   0,   0,   1,   2,   2,   2,  13,   2,   0,   0,   2,   2,   2,   4,
      5,  14,   8,   0,   0,   2,  13,   2,   4,   0,   0,   0,   5,   0,   0,   0,   0,   0,   0,   7,
      5,   6,   5,   0,   0,   0,   5,  14,   7,   0,   0,   0,   5,   0,   0,   0,   0,   0,   0,   7,
      5,  15,   5,   0,   0,   0,   5,  14,   7,   0,   0,   0,   5,   0,   0,   0,   0,   0,   0,   7,
      5,   6,   5,   0,   0,   0,   9,  10,   4,   0,   0,   0,   8,   3,   0,   0,   0,   0,   0,   7,
      5,  15,   5,   0,   0,   0,   0,   0,   7,   0,   0,   0,   9,  12,  10,  10,   0,   0,  10,   4,
      5,   6,   5,   0,   0,   0,   0,   0,   7,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   7,
      5,  14,   5,   0,   0,   0,   0,   0,   7,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   7,
      8,  10,  12,  10,   0,   0,  10,  10,  11,   0,   0,   0,   1,   2,   2,   3,   0,   0,   0,   7,
      5,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   5,   6,  15,   7,   0,   0,   0,   7,
      5,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   5,  14,   6,   7,   0,   0,   0,   7,
      5,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   8,  10,  10,  11,   0,   0,   0,   7,
      5,   0,   0,   1,   2,   0,   0,   2,  13,   2,   2,   2,   4,   0,   0,   0,   0,   0,   0,   7,
      5,   0,   0,   5,   0,   0,   0,   0,   7,  15,   6,   6,   7,   0,   0,   0,   0,   0,   0,   7,
      5,   0,   0,   5,   0,   0,   0,   0,   7,   6,   6,   6,   9,   3,   0,   0,   0,   0,   0,   7,
      5,   0,   0,   5,   0,   0,   0,   0,   7,  15,   6,   6,   6,   8,   2,   0,   0,   2,   2,   4,
      5,   0,   0,   5,   0,   0,   0,   0,   7,   6,   6,   6,  15,   5,   0,   0,   0,   0,   0,   7,
      5,   0,   0,   5,   0,   0,   0,   0,   7,  15,   6,   6,   6,   5,   0,   0,   0,   0,   0,   7,
      5,   0,   0,   5,   0,   0,   0,   0,   7,   6,   6,   6,  15,   5,   0,   0,   0,   0,   0,   7,
      9,  10,  10,  12,  10,   0,   0,  10,  12,  10,  10,  10,  10,  12,  10,  10,  10,  10,  10,  11,
}};

void draw_tile(const byte __memx *glyph, int x, int y);
void draw_map(const Map __memx *m, word x, word y);

#endif