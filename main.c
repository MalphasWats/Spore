#include <avr/io.h>

#include "main.h"

word t = 0;
word btn_timer = 0;

Viewport viewport = {.x=0, .y=0};

Sprite player = {.x=0, .y=0, .glyph=P_UP};
Stats status = {.health=12, .lives=3, .clips=2, .rounds=CLIP_SIZE, .keys=2};

Sprite muzzle = {.x=0, .y=0, .glyph=0};
Sprite bullet = {.x=0, .y=0, .glyph=0};

word shoot_timer = 0;
word shot_delay = 0;

const Level __memx *current_level;
LevelDoors *current_level_doors;
LevelItems *current_level_items;
MobList *current_level_mobs;

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
    current_level_doors = &LEVEL_1_DOORS;
    current_level_items = &LEVEL_1_ITEMS;
    current_level_mobs = &LEVEL_1_MOBS;
    
    player.x = current_level->start_x;
    player.y = current_level->start_y;
    
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
                
                vx = -1;
                player.glyph = P_LEFT;
            }
            else if(buttons & _RIGHT)
            {
                btn_timer = t+BTN_DELAY;
                
                vx = 1;
                player.glyph = P_RIGHT;
            }
            else if(buttons & _DOWN)
            {
                btn_timer = t+BTN_DELAY;
                
                vy = 1;
                player.glyph = P_DOWN;
            }
            else if(buttons & _UP)
            {
                btn_timer = t+BTN_DELAY;
                
                vy = -1;
                player.glyph = P_UP;
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
        
        if (shot_delay < t)
        {
            if(buttons & _A)
            {
                if (status.rounds > 0)
                {
                    status.rounds -= 1;
                    click();
                    
                    shoot_timer = t+SHOT_ANIM_DELAY;
                    
                    collision p = {.x=0, .y=0, .collisionType=WALL, .index=0};
                    
                    if (player.glyph == P_UP)
                    {
                        muzzle.glyph = F_UP;
                        muzzle.x = player.x-4;
                        muzzle.y = player.y-15;
                        
                        p = cast_to_collision(current_level, player.x, player.y, 0, -1);
                        bullet.x = p.x-4;
                        bullet.y = p.y+1;
                        
                        bullet.glyph = B_UP;
                    }
                    else if (player.glyph == P_DOWN)
                    {
                        muzzle.glyph = F_DOWN;
                        muzzle.x = player.x-5;
                        muzzle.y = player.y+6;
                        
                        p = cast_to_collision(current_level, player.x, player.y, 0, 1);
                        bullet.x = p.x-5;
                        bullet.y = p.y-9;
                        
                        bullet.glyph = B_DOWN;
                    }
                    else if (player.glyph == P_LEFT)
                    {
                        muzzle.glyph = F_LEFT;
                        muzzle.x = player.x-10;
                        muzzle.y = player.y-4;
                        
                        p = cast_to_collision(current_level, player.x, player.y, -1, 0);
                        bullet.x = p.x+1;
                        bullet.y = p.y-4;
                        
                        bullet.glyph = B_LEFT;
                    }
                    else if (player.glyph == P_RIGHT)
                    {
                        muzzle.glyph = F_RIGHT;
                        muzzle.x = player.x+2;
                        muzzle.y = player.y-4;
                        
                        p = cast_to_collision(current_level, player.x, player.y, 1, 0);
                        bullet.x = p.x-9;
                        bullet.y = p.y-4;
                        
                        bullet.glyph = B_RIGHT;
                    }
                    
                    if (p.collisionType == MOB)
                        current_level_mobs->mobs[p.index].health -= 1;
                    
                }
                else
                {
                    if (status.clips > 0)
                    {
                        status.clips -= 1;
                        status.rounds = CLIP_SIZE;
                    }
                    note(_A4, 10);
                }
                
                shot_delay = t+SHOT_DELAY;
            }
        }
        
        if (t >= btn_timer)
            btn_timer = 0;
        
        player.x += vx;
        if ( check_collision(current_level, player.x, player.y) )
            player.x -= vx;
        
        player.y += vy;
        if ( check_collision(current_level, player.x, player.y) )
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
        draw_level(current_level, viewport.x, viewport.y);
        
        draw_sprite(&player, &viewport);
        
        if (shoot_timer > t)
        {
            draw_tile(&GLYPHS[muzzle.glyph], muzzle.x-viewport.x, muzzle.y-viewport.y);
            draw_tile(&GLYPHS[bullet.glyph], bullet.x-viewport.x, bullet.y-viewport.y);
        }
        
        /* Draw Doors */
        for (byte i=0 ; i<current_level_doors->num_doors ; i++)
        {
            if (current_level_doors->doors[i].open)
            {
                draw_tile(&GLYPHS[DOOR_L_OPEN], current_level_doors->doors[i].x-viewport.x, current_level_doors->doors[i].y-viewport.y);
                draw_tile(&GLYPHS[DOOR_R_OPEN], (current_level_doors->doors[i].x+8)-viewport.x, current_level_doors->doors[i].y-viewport.y);
            }
            else
            {
                draw_tile(&GLYPHS[DOOR_L_CLOSED], current_level_doors->doors[i].x-viewport.x, current_level_doors->doors[i].y-viewport.y);
                draw_tile(&GLYPHS[DOOR_R_CLOSED], (current_level_doors->doors[i].x+8)-viewport.x, current_level_doors->doors[i].y-viewport.y);
            }
        }
        
        /* Draw Items */
        for (byte i=0 ; i<current_level_items->num_items ; i++)
        {
            if (!current_level_items->items[i].collected)
            {
                draw_tile(&GLYPHS[current_level_items->items[i].glyph], current_level_items->items[i].x-viewport.x, current_level_items->items[i].y-viewport.y);
            }
        }
        
        /* Draw Mobs */
        for (byte i=0 ; i<current_level_mobs->num_mobs ; i++)
        {
            if (current_level_mobs->mobs[i].health > 0)
            {
                if (current_level_mobs->mobs[i].timer >= t)
                {
                    if (current_level_mobs->mobs[i].sprite.glyph == M_RIGHT)
                    {
                        current_level_mobs->mobs[i].sprite.x += 1;
                        if (check_collision(current_level, current_level_mobs->mobs[i].sprite.x, current_level_mobs->mobs[i].sprite.y))
                        {
                            current_level_mobs->mobs[i].sprite.glyph = M_LEFT;
                            current_level_mobs->mobs[i].sprite.x -= 1;
                        }
                    }
                    else
                    {
                        current_level_mobs->mobs[i].sprite.x -= 1;
                        if (check_collision(current_level, current_level_mobs->mobs[i].sprite.x, current_level_mobs->mobs[i].sprite.y))
                        {
                            current_level_mobs->mobs[i].sprite.glyph = M_RIGHT;
                            current_level_mobs->mobs[i].sprite.x += 1;
                        }
                    }
                                    
                    current_level_mobs->mobs[i].timer = t+30;
                    
                    draw_sprite(&current_level_mobs->mobs[i].sprite, &viewport);
                }
            }
        }
               
        /* Display HUD on bottom row */
        for(byte i=0 ; i<SCREEN_WIDTH ; i++)
            buffer[7*SCREEN_WIDTH+i] = 0;
        
        draw_tile(&GLYPHS[HUD_HEALTH], 1*8, 7*8);
        for(byte i=0 ; i<status.health ; i++)
        {
            buffer[(7*SCREEN_WIDTH + 2*8) + 2*i] = 0x7c;
        }
        
        draw_tile(&GLYPHS[HUD_LIVES], 6*8, 7*8);
        for(byte i=0 ; i<status.lives ; i++)
        {
            buffer[(7*SCREEN_WIDTH + 7*8) + 2*i] = 0x7c;
        }
        
        draw_tile(&GLYPHS[HUD_AMMO], 9*8, 7*8);
        for(byte i=0 ; i<status.clips ; i++)
        {
            buffer[( 7*SCREEN_WIDTH + 10*8) + 2*i] = 0x7c;
        }
        byte r=status.rounds;
        byte i=0;
        while (r>1)
        {
            buffer[( 7*SCREEN_WIDTH + 11*8) + 2*i] = 0x6c;
            r >>= 1;
            i += 1;
        }
        if ( status.rounds & 1 )
            buffer[( 7*SCREEN_WIDTH + 11*8) + 2*i] = 0x60;
        
        draw_tile(&GLYPHS[HUD_KEYS], 13*8, 7*8);
        byte k=status.keys;
        i=0;
        while(k > 1)
        {
            buffer[( 7*SCREEN_WIDTH + 14*8) + 2*i] = 0x6c;
            k >>= 1;
            i += 1;
        }
        if ( status.keys & 1 )
            buffer[( 7*SCREEN_WIDTH + 14*8) + 2*i] = 0x60;
        
        draw();
    }
}

collision cast_to_collision(const Level __memx *lvl, int x, int y, int dx, int dy)
{
    CollisionTypes c = WALL;
    byte index = 0;
    while(lvl->tiles[ ( ( (y>>3) * lvl->cols) + (x>>3) ) ] == 0 &&
           x >= 0 && x < lvl->cols*8 && y >= 0 && y < lvl->rows*8)
    {
        
        for (byte i=0 ; i<current_level_mobs->num_mobs ; i++)
        {
            if (x >= current_level_mobs->mobs[i].sprite.x-8 &&
                x < current_level_mobs->mobs[i].sprite.x+8  &&
                y >= current_level_mobs->mobs[i].sprite.y-8 &&
                y < current_level_mobs->mobs[i].sprite.y+8  &&
                current_level_mobs->mobs[i].health > 0)         // Ugly but meh.
            {
                c = MOB;
                index = i;
            }
        }
        
        if (c == MOB)
            break;
        
        x += dx;
        y += dy;
    }
    
    //TODO: need to check doors too
    
    
    
    return (collision){.x=x, .y=y, .collisionType=c, .index=index};
}

bool check_collision(const Level __memx *lvl, word x, word y)
{
    if (lvl->tiles[ ( (( y >>3) * lvl->cols) + ( x >> 3) ) ] == 0)
    {
        for (byte i=0 ; i<current_level_doors->num_doors ; i++)
        {
            if (x >= current_level_doors->doors[i].x && 
                x < current_level_doors->doors[i].x+16 && 
                y >= current_level_doors->doors[i].y &&
                y < current_level_doors->doors[i].y+8 &&
                !current_level_doors->doors[i].open)
            {
                if (status.keys > 0)
                {
                    status.keys -= 1;
                    current_level_doors->doors[i].open = TRUE;
                    note(_A5, 10);
                    return FALSE;
                }
                else
                {
                    note(_A4, 10);
                    return TRUE;
                }
            }
        }
        
        for (byte i=0 ; i<current_level_items->num_items ; i++)
        {
            if (x >= current_level_items->items[i].x && 
                x < current_level_items->items[i].x+8 && 
                y >= current_level_items->items[i].y &&
                y < current_level_items->items[i].y+8 &&
                !current_level_items->items[i].collected)
            {
                note(_Cs5, 10);
                current_level_items->items[i].collected = TRUE;
                
                status.health += current_level_items->items[i].stats.health;
                status.lives += current_level_items->items[i].stats.lives;
                status.clips += current_level_items->items[i].stats.clips;
                status.keys += current_level_items->items[i].stats.keys;
                
                if (status.health > MAX_HEALTH)
                    status.health = MAX_HEALTH;
                
                //TODO: limit other items too
            }
        }
        
        return FALSE;
    }
    return TRUE;
}

void draw_level(const Level __memx *lvl, word x, word y)
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
            draw_tile(&GLYPHS[lvl->tiles[ lvl->cols * (row+y) + (col+x) ]*8], col*8-x_offset, row*8-y_offset); 
        }
    }
}

void draw_sprite(Sprite *s, Viewport *v)
{
    int x = s->x-v->x;
    int y = s->y-v->y;
    
    draw_tile(&GLYPHS[s->glyph], x-8, y-8);
    draw_tile(&GLYPHS[s->glyph+8], x, y-8);
    draw_tile(&GLYPHS[s->glyph+16], x-8, y);
    draw_tile(&GLYPHS[s->glyph+24], x, y);
}

void draw_tile(const byte __memx *glyph, int x, int y)
{
    /* is the tile actually visible
       Last one is y >= SCREEN_HEIGHT because of the HUD */
    if (x < -7 || x >= SCREEN_WIDTH+7 || y < -7 || y >= SCREEN_HEIGHT)
        return;
    
    
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
    
    if (x > SCREEN_WIDTH-8)
    {
        tile_width = SCREEN_WIDTH-x;
    }
    
    if (y < 0)
    {
        y_offset_a = 8;
        y_offset_b = 0-y;
        tile_start -= SCREEN_WIDTH;
    }
    
    if (y > SCREEN_HEIGHT-8)
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
