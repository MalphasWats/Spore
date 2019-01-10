#include <avr/io.h>

#include "main.h"

word t = 0;
word btn_timer = 0;

Viewport viewport = {.x=0, .y=0};

Sprite player = {.x=6*8, .y=32*8, .glyph=P_UP};

const Map __memx *current_level;

int main (void) 
{
    initialise();    
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
    
    int vx, vy;
    
    for(ever)
    {
        t = millis();
        
        vx = 0;
        vy = 0;
        
        buttons = ~PINC;
        if (btn_timer == 0)
        {
            if (buttons & _LEFT)
            {
                btn_timer = t+BTN_DELAY;
                
                //player.x -= 1;
                vx = -1;
                player.glyph = P_LEFT;
            }
            else if(buttons & _RIGHT)
            {
                btn_timer = t+BTN_DELAY;
                
                //player.x += 1;
                vx = 1;
                player.glyph = P_RIGHT;
            }
            else if(buttons & _DOWN)
            {
                btn_timer = t+BTN_DELAY;
                
                //player.y += 1;
                vy = 1;
                player.glyph = P_DOWN;
            }
            else if(buttons & _UP)
            {
                btn_timer = t+BTN_DELAY;
                
                //player.y -= 1;
                vy = -1;
                player.glyph = P_UP;
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
        
        player.x += vx;
        if (current_level->tiles[ ( (( player.y >>3) * current_level->cols) + ( player.x >> 3) ) ] > 0)
            player.x -= vx;
        
        player.y += vy;
        if (current_level->tiles[ ( (( player.y >>3) * current_level->cols) + ( player.x >> 3) ) ] > 0)
            player.y -= vy;
        
        //TODO: should check middle of player
        //      ALSO player is 16x16
        if (player.x < 0)
            player.x = 0;
        if (player.x > current_level->cols*8)
            player.x = current_level->cols*8;
        if (player.y < 0)
            player.y = 0;
        if (player.y > current_level->rows*8)
            player.y = current_level->rows*8;
        
        
        viewport.x = player.x-HALF_SCREEN_WIDTH;
        viewport.y = player.y-HALF_SCREEN_HEIGHT;
            
        if (viewport.x < 0)
            viewport.x = 0;
        if (viewport.y < 0)
            viewport.y = 0;
        
        if (viewport.x + SCREEN_WIDTH > current_level->cols*8)
            viewport.x = current_level->cols*8 - SCREEN_WIDTH;
        if (viewport.y + SCREEN_HEIGHT > current_level->rows*8+8)
            viewport.y = current_level->rows*8 - SCREEN_HEIGHT+8;
        
        clear_buffer();
        draw_map(current_level, viewport.x, viewport.y);
        
        draw_sprite(&player, &viewport);
               
        /* Display HUD on bottom row */
        for(byte i=0 ; i<SCREEN_WIDTH ; i++)
            buffer[7*SCREEN_WIDTH+i] = 0;
        draw_tile(&GLYPHS[HUD_HEALTH], 1*8, 7*8);
        draw_tile(&GLYPHS[HUD_LIVES], 6*8, 7*8);
        draw_tile(&GLYPHS[HUD_AMMO], 9*8, 7*8);
        draw_tile(&GLYPHS[HUD_KEYS], 13*8, 7*8);
        
        draw();
    }
}

void draw_map(const Map __memx *m, word x, word y)
{
    byte x_offset = x & 7; // x % 8
    x >>= 3;
    
    byte y_offset = y & 7; // y % 8
    y >>= 3;
    
    byte NUM_ROWS = SCREEN_ROWS-1;
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

void draw_sprite(Sprite *s, Viewport *v)
{
    draw_tile(&GLYPHS[s->glyph], (s->x-v->x)-8, (s->y-v->y)-8);
    draw_tile(&GLYPHS[s->glyph+8], s->x-v->x, (s->y-v->y)-8);
    draw_tile(&GLYPHS[s->glyph+16], (s->x-v->x)-8, s->y-v->y);
    draw_tile(&GLYPHS[s->glyph+24], s->x-v->x, s->y-v->y);
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
