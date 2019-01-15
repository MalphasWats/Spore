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
    
    0xff, 0x76, 0x14, 0x14, 0x14, 0x14, 0x1c, 0x08, // Door Left Closed
    0x08, 0x1c, 0x14, 0x14, 0x14, 0x14, 0x76, 0xff, // Door Right Closed
    0xff, 0x14, 0x08, 0x00, 0x00, 0x00, 0x00, 0x00, // Door Left  Open
    0x00, 0x00, 0x00, 0x00, 0x00, 0x08, 0x14, 0xff, // Door Right Open
    
    
    0x00, 0x00, 0x00, 0x00, 0xc0, 0x60, 0x18, 0xbe, // Player Idle Up TL
    0x90, 0x20, 0x60, 0xc0, 0x80, 0x00, 0x00, 0x00, // Player Idle Up TR
    0x00, 0x00, 0x06, 0x0f, 0x18, 0x36, 0x2d, 0x1e, // Player Idle Up BL
    0x1e, 0x2d, 0x36, 0x18, 0x0e, 0x07, 0x00, 0x00, // Player Idle Up BR
    
    0x00, 0x00, 0x00, 0x00, 0xd8, 0x68, 0x20, 0xb0, 
    0x90, 0x3e, 0x60, 0xc0, 0x80, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x06, 0x0f, 0x18, 0x36, 0x2d, 0x1e, 
    0x1e, 0x2d, 0x36, 0x58, 0x6e, 0x07, 0x00, 0x00,
    
    0x00, 0x00, 0x00, 0x00, 0xc0, 0x60, 0x18, 0xbe, 
    0x90, 0x20, 0x60, 0xd0, 0xb0, 0x00, 0x00, 0x00, 
    0x00, 0x00, 0x06, 0x6f, 0x58, 0x36, 0x2d, 0x1e, 
    0x1e, 0x2d, 0x36, 0x18, 0x0e, 0x07, 0x00, 0x00, 
    
    0x00, 0x00, 0x60, 0xb0, 0xd8, 0xec, 0xac, 0x48, // Player Right
    0x90, 0x30, 0xa0, 0xc0, 0xc0, 0x80, 0x80, 0x00, 
    0x00, 0x00, 0x06, 0x0d, 0x1b, 0x37, 0x35, 0x22, 
    0x19, 0x0c, 0x06, 0x01, 0x00, 0x00, 0x00, 0x00, 
    
    0x00, 0x00, 0x60, 0xb0, 0xd8, 0xec, 0xac, 0x48, 
    0x90, 0x30, 0xe0, 0x90, 0x30, 0x00, 0x00, 0x00, 
    0x00, 0x00, 0x36, 0x2d, 0x1b, 0x37, 0x35, 0x22, 
    0x19, 0x0c, 0x06, 0x03, 0x02, 0x02, 0x02, 0x00, 
    
    0x00, 0x00, 0x6c, 0xb4, 0xd8, 0xec, 0xac, 0x48, 
    0x90, 0x30, 0xa0, 0xc0, 0xc0, 0x80, 0x80, 0x00, 
    0x00, 0x00, 0x06, 0x0d, 0x1b, 0x37, 0x35, 0x22, 
    0x19, 0x0c, 0x16, 0x19, 0x00, 0x00, 0x00, 0x00, 
    
    0x00, 0x00, 0x60, 0xf0, 0x18, 0x6c, 0xb4, 0x78, // Player Down
    0x78, 0xb4, 0x6c, 0x18, 0x70, 0xe0, 0x00, 0x00, 
    0x00, 0x00, 0x00, 0x00, 0x03, 0x06, 0x18, 0x7d, 
    0x09, 0x04, 0x06, 0x03, 0x01, 0x00, 0x00, 0x00, 
        
    0x00, 0x00, 0x60, 0xf0, 0x18, 0x6c, 0xb4, 0x78, 
    0x78, 0xb4, 0x6c, 0x1a, 0x76, 0xe0, 0x00, 0x00, 
    0x00, 0x00, 0x00, 0x00, 0x03, 0x06, 0x18, 0x7d, 
    0x09, 0x04, 0x06, 0x0b, 0x0d, 0x00, 0x00, 0x00, 
    
    0x00, 0x00, 0x60, 0xf6, 0x1a, 0x6c, 0xb4, 0x78, 
    0x78, 0xb4, 0x6c, 0x18, 0x70, 0xe0, 0x00, 0x00, 
    0x00, 0x00, 0x00, 0x00, 0x1b, 0x16, 0x04, 0x0d, 
    0x09, 0x7c, 0x06, 0x03, 0x01, 0x00, 0x00, 0x00, 
    
    
    0x00, 0x80, 0x80, 0xc0, 0xc0, 0xa0, 0x30, 0x90, // Player Left
    0x48, 0xac, 0xec, 0xd8, 0xb0, 0x60, 0x00, 0x00, 
    0x00, 0x00, 0x00, 0x00, 0x01, 0x06, 0x0c, 0x19, 
    0x22, 0x35, 0x37, 0x1b, 0x0d, 0x06, 0x00, 0x00,
    
    0x00, 0x00, 0x00, 0x30, 0x90, 0xe0, 0x30, 0x90, 
    0x48, 0xac, 0xec, 0xd8, 0xb0, 0x60, 0x00, 0x00, 
    0x00, 0x00, 0x00, 0x00, 0x19, 0x16, 0x0c, 0x19, 
    0x22, 0x35, 0x37, 0x1b, 0x0d, 0x06, 0x00, 0x00, 
    
    0x00, 0x80, 0x80, 0xc0, 0xc0, 0xa0, 0x30, 0x90, 
    0x48, 0xac, 0xec, 0xd8, 0xb4, 0x6c, 0x00, 0x00,  
    0x00, 0x02, 0x02, 0x02, 0x03, 0x06, 0x0c, 0x19, 
    0x22, 0x35, 0x37, 0x1b, 0x2d, 0x36, 0x00, 0x00, 
    
    0x7e, 0x81, 0xb5, 0xa5, 0xa5, 0xb5, 0x81, 0x7e, // Clip pickup (72)
    0x7e, 0x81, 0x99, 0xbd, 0xbd, 0x99, 0x81, 0x7e, // Health pickup
    0x76, 0x89, 0x95, 0x89, 0x89, 0x99, 0x81, 0x7e, // Key pickup
    0x66, 0x99, 0xbd, 0x79, 0x79, 0xbd, 0x99, 0x66, // Life pickup
    
    0x00, 0x02, 0x01, 0x03, 0x01, 0x02, 0x00, 0x00, // Bullet hit UP (76)
    0x00, 0x00, 0x40, 0x80, 0xc0, 0x80, 0x40, 0x00, // Bullet hit DOWN
    0x1c, 0x2a, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, // Bullet hit LEFT
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x2a, 0x1c, // Bullet hit RIGHT
    0x00, 0xa0, 0xc0, 0x60, 0xc0, 0xa0, 0x00, 0x00, // Muzzle Flash UP
    0x00, 0x00, 0x05, 0x03, 0x06, 0x03, 0x05, 0x00, // Muzzle Flash DOWN
    0x36, 0x1c, 0x2a, 0x00, 0x00, 0x00, 0x00, 0x00, // Muzzle Flash LEFT
    0x00, 0x00, 0x00, 0x00, 0x00, 0x2a, 0x1c, 0x36, // Muzzle Flash RIGHT
};

#define HUD_HEALTH 16*8
#define HUD_LIVES 17*8
#define HUD_AMMO 18*8
#define HUD_KEYS 19*8

#define KEY_PICKUP 74*8

#define P_UP        24*8
#define P_RIGHT     36*8
#define P_DOWN      48*8
#define P_LEFT      60*8

#define B_UP        76*8
#define B_DOWN      77*8
#define B_LEFT      78*8
#define B_RIGHT     79*8

#define F_UP        80*8
#define F_DOWN      81*8
#define F_LEFT      82*8
#define F_RIGHT     83*8


#define DOOR_L_CLOSED   20*8
#define DOOR_R_CLOSED   21*8
#define DOOR_L_OPEN     22*8
#define DOOR_R_OPEN     23*8


typedef struct Sprite {
    int x;
    int y;
    
    word glyph;
} Sprite;

typedef struct Door {
    int x;
    int y;
    bool open;
} Door;

#define MAX_DOORS 5

typedef struct Level {
    int start_x;
    int start_y;
    word cols;
    word rows;
    byte tiles[];
} Level;

typedef struct LevelDoors {
    byte num_doors;
    Door doors[];
} LevelDoors;


typedef struct Stats {
    byte health;
    byte lives;
    byte clips;
    byte rounds;
    byte keys;
} Stats;

#define MAX_HEALTH 12
#define CLIP_SIZE 12

#define SHOT_DELAY 80
#define SHOT_ANIM_DELAY 20

typedef struct Item {
    int x;
    int y;
    word glyph;
    Stats stats;
    bool collected;
} Item;

#define MAX_ITEMS 12
typedef struct LevelItems {
    byte num_items;
    Item items[MAX_ITEMS];
} LevelItems;


LevelDoors LEVEL_1_DOORS = {
        .num_doors = 6,
        .doors = {
            {.x=4*8, .y=23*8, .open=FALSE},
            {.x=5*8, .y=27*8, .open=FALSE},
            {.x=3*8, .y=16*8, .open=FALSE},
            {.x=14*8, .y=15*8, .open=FALSE},
            {.x=16*8, .y=20*8, .open=FALSE},
            {.x=15*8, .y=30*8, .open=FALSE},
        }
};

LevelItems LEVEL_1_ITEMS = {
    .num_items=1,
    .items = {
        {.x=2*8, .y=32*8, .glyph=KEY_PICKUP, .stats={.health=0, .lives=0, .clips=0, .rounds=0, .keys=1}, .collected=FALSE},
    }
};
        

static const __flash Level LEVEL_1 = {
        .start_x = 6*8,
        .start_y = 32*8,
        .cols = 20,
        .rows = 35,
        .tiles = {
      1,   2,   2,   2,   2,   2,   2,  20,  21,   2,   2,   2,   2,   2,   2,   2,   2,   2,   2,   3,
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
      9,  10,  10,  12,  10,  20,  21,  10,  12,  10,  10,  10,  10,  12,  10,  10,  10,  10,  10,  11,
            }
};

bool check_collision(const Level __memx *lvl, word x, word y);

void draw_tile(const byte __memx *glyph, int x, int y);
void draw_level(const Level __memx *lvl, word x, word y);
void draw_sprite(Sprite *s, Viewport *v);

#endif