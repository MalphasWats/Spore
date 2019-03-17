#include "spore.h"

const __flash Map* current_level;
const __flash LevelDoors* current_level_doors;
const __flash LevelItems* current_level_items;

const __flash MobList* current_level_mobs;

uint8_t door_status[MAX_DOORS];
uint8_t item_status[MAX_ITEMS];

MobList mobs;

Stats status = {.health=12, .lives=3, .clips=2, .rounds=CLIP_SIZE, .keys=2};
Sprite player = {.x=6*8, .y=32*8, .width=16, .height=16, .tile=P_UP, .mask=&BLOCK_MASKS[TRANSPARENT]};


void spore (void) 
{
    uint32_t t = 0;
    uint32_t move_timer = 0;
    uint32_t shoot_timer = 0;
    
    uint8_t buttons = 0;
    
    current_level = &LEVEL_1;
    current_level_doors = &LEVEL_1_DOORS;
    current_level_items = &LEVEL_1_ITEMS;
    
    current_level_mobs = &LEVEL_1_MOBS;
    
    for (uint8_t i=0 ; i<MAX_DOORS ; i++)
        door_status[i] = CLOSED;
        
    for (uint8_t i=0 ; i<MAX_ITEMS ; i++)
        item_status[i] = UNCOLLECTED;
        
    mobs.num_mobs = current_level_mobs->num_mobs;
    for (uint8_t i=0 ; i<MAX_MOBS ; i++)
        mobs.mobs[i] = current_level_mobs->mobs[i];
    
    int16_t vx, vy;
    
    Sprite muzzle = {.x=0, .y=0, .width=8, .height=8, .tile=&TILES[0], .mask=&BLOCK_MASKS[TRANSPARENT]};
    Sprite bullet = {.x=0, .y=0, .width=8, .height=8, .tile=&TILES[0], .mask=&BLOCK_MASKS[TRANSPARENT]};
    
    for(ever)
    {
        t = millis();
        
        buttons = read_buttons();
        if (move_timer <= t)
        {
            vx = 0;
            vy = 0;
            
            if (buttons & BTN_LEFT)
            {
                move_timer = t+MOVE_DELAY;
                
                vx = -1;
                player.tile = P_LEFT;
            }
            else if(buttons & BTN_RIGHT)
            {
                move_timer = t+MOVE_DELAY;
                
                vx = 1;
                player.tile = P_RIGHT;
            }
            else if(buttons & BTN_DOWN)
            {
                move_timer = t+MOVE_DELAY;
                
                vy = 1;
                player.tile = P_DOWN;
            }
            else if(buttons & BTN_UP)
            {
                move_timer = t+MOVE_DELAY;
                
                vy = -1;
                player.tile = P_UP;
            }
            
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
        }
        
        if (shoot_timer < t)
        {
            if(buttons & BTN_A)
            {
                if (status.rounds > 0)
                {
                    status.rounds -= 1;
                    click();
                    
                    shoot_timer = t+SHOT_ANIM_DELAY;
                    
                    collision p = {.x=0, .y=0, .collisionType=WALL, .index=0};
                    
                    if (player.tile == P_UP)
                    {
                        muzzle.tile = F_UP;
                        muzzle.x = player.x;
                        muzzle.y = player.y-12;
                        
                        p = cast_to_collision(current_level, player.x, player.y, 0, -1);
                        bullet.x = p.x;
                        bullet.y = p.y+5;
                        
                        bullet.tile = B_UP;
                    }
                    else if (player.tile == P_DOWN)
                    {
                        muzzle.tile = F_DOWN;
                        muzzle.x = player.x-1;
                        muzzle.y = player.y+12;
                        
                        p = cast_to_collision(current_level, player.x, player.y, 0, 1);
                        bullet.x = p.x-1;
                        bullet.y = p.y-5;
                        
                        bullet.tile = B_DOWN;
                    }
                    else if (player.tile == P_LEFT)
                    {
                        muzzle.tile = F_LEFT;
                        muzzle.x = player.x-7;
                        muzzle.y = player.y;
                        
                        p = cast_to_collision(current_level, player.x, player.y, -1, 0);
                        bullet.x = p.x+6;
                        bullet.y = p.y;
                        
                        bullet.tile = B_LEFT;
                    }
                    else if (player.tile == P_RIGHT)
                    {
                        muzzle.tile = F_RIGHT;
                        muzzle.x = player.x+7;
                        muzzle.y = player.y;
                        
                        p = cast_to_collision(current_level, player.x, player.y, 1, 0);
                        bullet.x = p.x-4;
                        bullet.y = p.y;
                        
                        bullet.tile = B_RIGHT;
                    }
                    
                    if (p.collisionType == MOB)
                    {
                        mobs.mobs[p.index].health -= 1;
                        mobs.mobs[p.index].move_timer += 250;
                        mobs.mobs[p.index].attack_timer += 60;
                        //TODO: define these numbers.
                    }
                    
                    draw_sprite(&muzzle);
                    draw_sprite(&bullet);
                }
                else
                {
                    if (status.clips > 0)
                    {
                        status.clips -= 1;
                        status.rounds = CLIP_SIZE;
                    }
                    else 
                    {
                        muzzle.tile = &TILES[0];
                        bullet.tile = &TILES[0];
                    }
                    note(_A4, 10);
                }
                
                shoot_timer = t+SHOT_DELAY;
            }
        }
            
            
        center_on_sprite(&player, current_level);
        
        clear_buffer();
        
        draw_map(current_level);
        
        Sprite tmp = {.x=0, .y=0, .width=16, .height=8, .mask=&BLOCK_MASKS[TRANSPARENT]};
        
        /* draw doors */
        for (uint8_t i=0 ; i<current_level_doors->num_doors ; i++)
        {
            tmp.x = current_level_doors->doors[i].x;
            tmp.y = current_level_doors->doors[i].y;
            if (door_status[i] == OPEN)
            {
                tmp.tile = DOOR_OPEN;
            }
            else
            {
                tmp.tile = DOOR_CLOSED;
            }
            
            draw_sprite(&tmp);
        }
        
        /* draw items */
        tmp.width = 8;
        for (uint8_t i=0 ; i<current_level_items->num_items ; i++)
        {
            if (item_status[i] == UNCOLLECTED)
            {
                tmp.tile = current_level_items->items[i].tile;
                tmp.x = current_level_items->items[i].x;
                tmp.y = current_level_items->items[i].y;
                
                draw_sprite(&tmp);
            }
        }
        
        /* Draw Mobs */
        for (uint8_t i=0 ; i<mobs.num_mobs ; i++)
        {
            
            if (mobs.mobs[i].move_timer <= t && mobs.mobs[i].health > 0)
            {
                if (mobs.mobs[i].sprite.tile == M_RIGHT)
                {
                    mobs.mobs[i].sprite.x += 1;
                    if (check_collision(current_level, mobs.mobs[i].sprite.x, mobs.mobs[i].sprite.y))
                    {
                        mobs.mobs[i].sprite.tile = M_LEFT;
                        mobs.mobs[i].sprite.x -= 1;
                    }
                }
                else
                {
                    mobs.mobs[i].sprite.x -= 1;
                    if (check_collision(current_level, mobs.mobs[i].sprite.x, mobs.mobs[i].sprite.y))
                    {
                        mobs.mobs[i].sprite.tile = M_RIGHT;
                        mobs.mobs[i].sprite.x += 1;
                    }
                }
                
                /* is the player nearby? */
                if (player.x > mobs.mobs[i].sprite.x-8 &&
                    player.x < mobs.mobs[i].sprite.x+8 &&
                    player.y > mobs.mobs[i].sprite.y-8 &&
                    player.y < mobs.mobs[i].sprite.y+8 &&
                    mobs.mobs[i].attack_timer <= t      &&
                    mobs.mobs[i].health > 0)
                {
                    status.health -= 1;
                    mobs.mobs[i].attack_timer = t+120;
                }
                                
                mobs.mobs[i].move_timer = t+40;
                //TODO: define delay numbers above.
                
            }
                
            if (mobs.mobs[i].health > 0)
            {
                draw_sprite(&mobs.mobs[i].sprite);
            }
        }
        
        if (shoot_timer > t)
        {
            draw_sprite(&muzzle);
            draw_sprite(&bullet);
        }
        
        //TODO: For testing
        if(status.health <= 0)
            status.health = 0;
        
        draw_sprite(&player);
        
               
        /* Display HUD on bottom row */
        for(uint8_t i=0 ; i<SCREEN_WIDTH ; i++)
            buffer[7*SCREEN_WIDTH+i] = 0;
        
        draw_tile(&TILES[HUD_HEALTH], &BLOCK_MASKS[OPAQUE], 1*8, 7*8);
        for(uint8_t i=0 ; i<status.health ; i++)
        {
            buffer[(7*SCREEN_WIDTH + 2*8) + 2*i] = 0x7c;
        }
        
        draw_tile(&TILES[HUD_LIVES], &BLOCK_MASKS[OPAQUE], 6*8, 7*8);
        for(uint8_t i=0 ; i<status.lives ; i++)
        {
            buffer[(7*SCREEN_WIDTH + 7*8) + 2*i] = 0x7c;
        }
        
        draw_tile(&TILES[HUD_AMMO], &BLOCK_MASKS[OPAQUE], 9*8, 7*8);
        for(uint8_t i=0 ; i<status.clips ; i++)
        {
            buffer[( 7*SCREEN_WIDTH + 10*8) + 2*i] = 0x7c;
        }
        uint8_t r=status.rounds;
        uint8_t i=0;
        while (r>1)
        {
            buffer[( 7*SCREEN_WIDTH + 11*8) + 2*i] = 0x6c;
            r -= 2;
            i += 1;
        }
        if ( status.rounds & 1 )
            buffer[( 7*SCREEN_WIDTH + 11*8) + 2*i] = 0x60;
        
        draw_tile(&TILES[HUD_KEYS], &BLOCK_MASKS[OPAQUE], 13*8, 7*8);
        uint8_t k=status.keys;
        i=0;
        while(k > 1)
        {
            buffer[( 7*SCREEN_WIDTH + 14*8) + 2*i] = 0x6c;
            k -= 2;
            i += 1;
        }
        if ( status.keys & 1 )
            buffer[( 7*SCREEN_WIDTH + 14*8) + 2*i] = 0x60;
        
        draw();
    }
}

collision cast_to_collision(const Map __flash *lvl, int16_t x, int16_t y, int16_t dx, int16_t dy)
{
    CollisionTypes c = WALL;
    uint8_t index = 0;
    while(lvl->tiles[ ( ( (y>>3) * lvl->cols) + (x>>3) ) ] == 0 &&
           x >= 0 && x < lvl->cols*8 && y >= 0 && y < lvl->rows*8)
    {
        
        index = collide_with_mob(x, y);
        if (index < mobs.num_mobs)
        {
            c = MOB;
            break;
        }
        
        x += dx;
        y += dy;
    }
    
    //TODO: need to check doors too
    
    return (collision){.x=x, .y=y, .collisionType=c, .index=index};
}

uint8_t collide_with_mob(uint16_t x, uint16_t y)
{
    for (uint8_t i=0 ; i<mobs.num_mobs ; i++)
    {
        if (x >= mobs.mobs[i].sprite.x-8 &&
            x < mobs.mobs[i].sprite.x+8  &&
            y >= mobs.mobs[i].sprite.y-8 &&
            y < mobs.mobs[i].sprite.y+8  &&
            mobs.mobs[i].health > 0)
        {
            return i;
        }
    }
    return mobs.num_mobs;
}

bool collide_with_door(uint16_t x, uint16_t y)
{
    for (uint8_t i=0 ; i<current_level_doors->num_doors ; i++)
    {
        if (x >= current_level_doors->doors[i].x-8 && 
            x < current_level_doors->doors[i].x+8 && 
            y >= current_level_doors->doors[i].y-4 &&
            y < current_level_doors->doors[i].y+4 &&
            door_status[i] == CLOSED)
        {
            if (status.keys > 0)
            {
                status.keys -= 1;
                door_status[i] = OPEN;
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
    return FALSE;
}

void collide_with_item(uint16_t x, uint16_t y)
{
    for (uint8_t i=0 ; i<current_level_items->num_items ; i++)
    {
        if (x >= current_level_items->items[i].x-4 && 
            x < current_level_items->items[i].x+4 && 
            y >= current_level_items->items[i].y-4 &&
            y < current_level_items->items[i].y+4 &&
            item_status[i] != COLLECTED)
        {
            note(_Cs5, 10);
            item_status[i] = COLLECTED;
            
            status.health += current_level_items->items[i].stats.health;
            status.lives += current_level_items->items[i].stats.lives;
            status.clips += current_level_items->items[i].stats.clips;
            status.keys += current_level_items->items[i].stats.keys;
            
            if (status.health > MAX_HEALTH)
                status.health = MAX_HEALTH;
            
            //TODO: limit other items too
        }
    }
    
}

bool check_collision(const Map __flash *lvl, uint16_t x, uint16_t y)
{
    if (lvl->tiles[ ( (( y >>3) * lvl->cols) + ( x >> 3) ) ] == 0)
    {
        if (collide_with_door(x, y))
            return TRUE;

        collide_with_item(x, y);
        
        return FALSE;
    }
    return TRUE;
}

