#include <avr/io.h>

#include "main.h"

word t = 0;
word btn_timer = 0;

byte buffer[SCREEN_WIDTH];

int viewport_x = 0;
int viewport_y = 0;

sprite sprites[MAX_SPRITES];
sprite* player;
level* levels[MAX_LEVELS];
level* current_level;

int main (void) 
{    
    initialise();
        
    display_image(&LOGO[0], 3, 3, 10, 2);
    crap_beep(_A5, 140);
    delay_ms(5);
    crap_beep(_A8, 60);
    
    delay_ms(SPLASH_DELAY);
    
    /* Build World */
    levels[0] = &(level){.map = &LEVEL_1[0], .width=20, .height=35};
    
    current_level = levels[0];
    
    /* Create Sprites */
    sprites[0] = (sprite){.glyph=PLAYER_SPRITE, .x=8, .y=8, .timer=0};
    player = &sprites[0];
    
    for(ever)
    {
        t = millis();
        
        word btn_val = read_buttons();
        if (btn_timer == 0)
        {
            if (btn_val >= _UP-BTN_THRESHOLD && btn_val <= _UP+BTN_THRESHOLD)
            {
                click();
                btn_timer = t+BTN_DELAY;
                
                player->x -= 1;
            }
            else if(btn_val >= _DOWN-BTN_THRESHOLD && btn_val <= _DOWN+BTN_THRESHOLD)
            {
                click();
                btn_timer = t+BTN_DELAY;
                
                player->x += 1;
            }
            else if(btn_val >= _LEFT-BTN_THRESHOLD && btn_val <= _LEFT+BTN_THRESHOLD)
            {
                click();
                btn_timer = t+BTN_DELAY;
                
                player->y -= 1;
            }
            else if(btn_val >= _RIGHT-BTN_THRESHOLD && btn_val <= _RIGHT+BTN_THRESHOLD)
            {
                click();
                btn_timer = t+BTN_DELAY;
                
                player->y += 1;
            }
            else if(btn_val >= _A-BTN_THRESHOLD && btn_val <= _A+BTN_THRESHOLD)
            {
                click();
                btn_timer = t+BTN_DELAY;
            }
            else if(btn_val >= _B-BTN_THRESHOLD && btn_val <= _B+BTN_THRESHOLD)
            {
                click();
                btn_timer = t+BTN_DELAY;
            }
            else if(btn_val >= _C-BTN_THRESHOLD && btn_val <= _C+BTN_THRESHOLD)
            {
                click();
                btn_timer = t+BTN_DELAY;
            }
        }
        
        if (t >= btn_timer)
            btn_timer = 0;
        
        // Update Viewport
        // Limit Viewport to Map
        
        viewport_x = player->x-SCREEN_WIDTH/2;
        viewport_y = player->y-SCREEN_HEIGHT/2;
            
        if (viewport_x < 0)
            viewport_x = 0;
        if (viewport_y < 0)
            viewport_y = 0;
        
        if (viewport_x + SCREEN_WIDTH > current_level->width*8)
            viewport_x = current_level->width*8 - SCREEN_WIDTH;
        if (viewport_y + SCREEN_HEIGHT > current_level->height*8)
            viewport_y = current_level->height*8 - SCREEN_HEIGHT;
        
        set_display_col_row(0, 0);
        for (byte row=0 ; row<SCREEN_ROWS-1 ; row++) // Map only displayed in first 7 rows.
        {
            for (byte col=0 ; col<SCREEN_COLUMNS ; col++)
            {
                // calculate map index
                // work out offsets
                // write to buffer
                //shift_out_block(&GLYPHS[LEVEL_1[ SCREEN_COLUMNS * row + col ]*8], FALSE);
                word index = (current_level->width * row + col);
                
                buffer[col*8+0] = GLYPHS[current_level->map[ index ]*8+0];
                buffer[col*8+1] = GLYPHS[current_level->map[ index ]*8+1];
                buffer[col*8+2] = GLYPHS[current_level->map[ index ]*8+2];
                buffer[col*8+3] = GLYPHS[current_level->map[ index ]*8+3];
                buffer[col*8+4] = GLYPHS[current_level->map[ index ]*8+4];
                buffer[col*8+5] = GLYPHS[current_level->map[ index ]*8+5];
                buffer[col*8+6] = GLYPHS[current_level->map[ index ]*8+6];
                buffer[col*8+7] = GLYPHS[current_level->map[ index ]*8+7];
            }
            
            // draw buffer
            for (byte x=0 ; x<SCREEN_WIDTH ; x++)
                shift_out_byte(buffer[x]);
        }
        
        /* Display HUD on bottom row */
        
        
    }
}
