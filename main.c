#include <avr/io.h>

#include "main.h"

word t = 0;
word btn_timer = 0;

Viewport viewport = {.x=0, .y=0};

const Map *current_level;

int main (void) 
{    
    // display logo
    for(byte y=0 ; y<LOGO_HEIGHT ; y++)
        for(byte x=0 ; x<LOGO_WIDTH ; x++)
            buffer[(y+2)*SCREEN_WIDTH + (x+16)] = LOGO[y*LOGO_WIDTH + x];
    draw();
    
    note(_A4, 90);
    delay_ms(180);
    note(_C5, 60);
    delay_ms(120);
    note(_E5, 60);
    
    delay_ms(SPLASH_DELAY);
    
    byte buttons = 0;
    
    current_level = &LEVEL_1;
    
    for(ever)
    {
        t = millis();
        
        buttons = ~PINC;
        if (btn_timer == 0)
        {
            if (buttons & _LEFT)
            {
                click();
                btn_timer = t+BTN_DELAY;
                
                viewport.x -= 1;
            }
            else if(buttons & _RIGHT)
            {
                click();
                btn_timer = t+BTN_DELAY;
                
                viewport.x += 1;
            }
            else if(buttons & _DOWN)
            {
                click();
                btn_timer = t+BTN_DELAY;
                
                viewport.y -= 1;
            }
            else if(buttons & _UP)
            {
                click();
                btn_timer = t+BTN_DELAY;
                
                viewport.y += 1;
            }
            else if(buttons & _A)
            {
                click();
                btn_timer = t+BTN_DELAY;
            }
            else if(buttons & _B)
            {
                click();
                btn_timer = t+BTN_DELAY;
            }
            else if(buttons & _C)
            {
                click();
                btn_timer = t+BTN_DELAY;
            }
        }
        
        if (t >= btn_timer)
            btn_timer = 0;
        
        // Update Viewport
        // Limit Viewport to Map
        
        //viewport.x = player->x-SCREEN_WIDTH/2;
        //viewport.y = player->y-SCREEN_HEIGHT/2;
            
        if (viewport.x < 0)
            viewport.x = 0;
        if (viewport.y < 0)
            viewport.y = 0;
        
        if (viewport.x + SCREEN_WIDTH > current_level->cols*8)
            viewport.x = current_level->cols*8 - SCREEN_WIDTH;
        if (viewport.y + SCREEN_HEIGHT > current_level->rows*8)
            viewport.y = current_level->rows*8 - SCREEN_HEIGHT;
        
        draw_map(current_level, viewport.x, viewport.y);
               
        /* Display HUD on bottom row */
        
        
    }
}

void draw_map(const Map __memx *m, word x, word y)
{
    byte x_offset = x & 7; // x % 8
    x >>= 3;
    
    byte y_offset = y & 7; // y % 8
    y >>= 3;
    
    byte NUM_ROWS = SCREEN_ROWS;
    if (y_offset > 0)
        NUM_ROWS += 1;
    
    byte NUM_COLS = SCREEN_COLUMNS;
    if (x_offset > 0)
        NUM_COLS += 1;
    
    for (byte row=0 ; row<NUM_ROWS ; row++)
    {
        for (byte col=0 ; col<NUM_COLS ; col++)
        {
            draw_tile(&GLYPHS[m->tiles[ m->cols * (row+y) + (col+x) ]*8], col*8-x_offset, row*8-y_offset); 
        }
    }
}

void draw_tile(const byte __memx *glyph, int x, int y)
{
    int y_ = y;
    
    if (y < 0)
        y_ = 0-y;
        
    int tile_start = ((y_ >> 3) * SCREEN_WIDTH) + x;
    
    byte y_offset_a = y & 7; // y % 8
    byte y_offset_b = 8-y_offset_a;
    
    byte glyph_index = 0;
    byte tile_width = 8;
    if (x < 0)
    {
        tile_start -= x;
        glyph_index = 0-x;
        tile_width -= glyph_index;
    }
    
    if (x > 120)
    {
        tile_width = 128-x;
    }
    
    if (y < 0)
    {
        y_offset_a = 8;
        y_offset_b = 0-y;
        tile_start -= SCREEN_WIDTH;
    }
    
    if (y > 56)
    {
        y_offset_b = 8;
    }
    
    for(byte tile_offset=0 ; tile_offset<tile_width ; tile_offset++, glyph_index++)
    {
        if (y_offset_a < 8)
            buffer[tile_start+tile_offset] |= glyph[glyph_index] << y_offset_a;
        if (y_offset_b < 8)
            buffer[tile_start+SCREEN_WIDTH+tile_offset] |= glyph[glyph_index] >> y_offset_b;
    }
}
