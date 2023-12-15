/*   
 * Copyright (C) 2008 - 2011 The OpenTitus team
 *
 * Authors:
 * Eirik Stople
 *
 * "Titus the Fox: To Marrakech and Back" (1992) and
 * "Lagaf': Les Aventures de Moktar - Vol 1: La Zoubida" (1991)
 * was developed by, and is probably copyrighted by Titus Software,
 * which, according to Wikipedia, stopped buisness in 2005.
 *
 * OpenTitus is not affiliated with Titus Software.
 *
 * OpenTitus is  free software; you can redistribute  it and/or modify
 * it under the  terms of the GNU General  Public License as published
 * by the Free  Software Foundation; either version 3  of the License,
 * or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful, but
 * WITHOUT  ANY  WARRANTY;  without   even  the  implied  warranty  of
 * MERCHANTABILITY or  FITNESS FOR A PARTICULAR PURPOSE.   See the GNU
 * General Public License for more details.
 */

/* engine.c
 * Engine functions
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "SDL2/SDL.h"
#include "sqz.h"
#include "settings.h"
#include "fonts.h"
#include "window.h"
#include "engine.h"
#include "tituserror.h"
#include "original.h"
#include "sprites.h"
#include "level.h"
#include "keyboard.h"
#include "globals.h"
#include "player.h"
#include "scroll.h"
#include "draw.h"
#include "reset.h"
#include "gates.h"
#include "elevators.h"
#include "objects.h"
#include "enemies.h"
#include "viewimage.h"

#include "audio.h"

static int playlevel(ScreenContext *context, TITUS_level *level);
static void death(ScreenContext *context, TITUS_level *level);
static void gameover(ScreenContext *context, TITUS_level *level);

int playtitus(int firstlevel){
    ScreenContext context;
    screencontext_reset(&context);

    int retval;

    TITUS_level level;
    unsigned char *leveldata;
    unsigned char *spritedata;
    TITUS_spritecache spritecache;
    TITUS_spritedata **sprites;
    uint16_t sprite_count;
    TITUS_objectdata **objects;
    uint16_t object_count;
    int leveldatasize;
    bool first;

    level.lives = 2;
    level.extrabonus = 0;

    retval = loadpixelformat(&(level.pixelformat));
    if (retval < 0) {
        freepixelformat(&(level.pixelformat));
        return retval;
    }

    retval = unSQZ(spritefile, &spritedata);
    if (retval < 0) {
        free (spritedata);
        freepixelformat(&(level.pixelformat));
        return retval;
    }
    retval = loadsprites(&sprites, spritedata, retval, level.pixelformat, &sprite_count);
    free (spritedata);
    if (retval < 0) {
        freesprites(&sprites, sprite_count);
        freepixelformat(&(level.pixelformat));
        return retval;
    }
    retval = initspritecache(&spritecache, 100, 3); //Cache size: 100 surfaces, 3 temporary
    if (retval < 0) {
        freespritecache(&spritecache);
        freesprites(&sprites, sprite_count);
        freepixelformat(&(level.pixelformat));
        return retval;
    }

    retval = loadobjects(&objects, &object_count);
    if (retval < 0) {
        freeobjects(&objects, object_count);
        freespritecache(&spritecache);
        freesprites(&sprites, sprite_count);
        freepixelformat(&(level.pixelformat));
        return retval;
    }

    for (level.levelnumber = firstlevel; level.levelnumber < levelcount; level.levelnumber++) {
        //strcpy (level.title, leveltitle[level.levelnumber]);
        level.levelid = getlevelid(level.levelnumber);
        retval = unSQZ(levelfiles[level.levelnumber], &leveldata);
        if (retval < 0) {
            free (leveldata);
            freeobjects(&objects, object_count);
            freespritecache(&spritecache);
            freesprites(&sprites, sprite_count);
            freepixelformat(&(level.pixelformat));
            return retval;
        }
        leveldatasize = retval;

        retval = loadlevel(&level, leveldata, leveldatasize, sprites, &(spritecache), objects);
        free (leveldata);
        if (retval < 0) {
            freelevel (&level);
            freeobjects(&objects, object_count);
            freespritecache(&spritecache);
            freesprites(&sprites, sprite_count);
            freepixelformat(&(level.pixelformat));
            return retval;
        }
        first = true;
        while (1) {
            SELECT_MUSIC(0);
            CLEAR_DATA(&level);

            GODMODE = false;
            NOCLIP = false;
            DISPLAYLOOPTIME = false;

            retval = viewstatus(&level, first);
            first = false;
            if (retval < 0) {
                freelevel (&level);
                freeobjects(&objects, object_count);
                freespritecache(&spritecache);
                freesprites(&sprites, sprite_count);
                freepixelformat(&(level.pixelformat));
                return retval;
            }

            //retval = initlevel (&level);

            //changemusic(modulelevelfile[modulelevel[level.levelnumber] - 1], modulelevelfileloop[modulelevel[level.levelnumber] - 1]);
            SELECT_MUSIC(LEVEL_MUSIC[level.levelid]);

            INIT_SCREENM(&context, &level); //Todo: comment, DOCUMENTED! (reset_level_simplified)
            DISPLAY_TILES(&level);
            flip_screen(&context, true);


            retval = playlevel (&context, &level);
            if (retval < 0) {
                freelevel (&level);
                freeobjects(&objects, object_count);
                freespritecache(&spritecache);
                freesprites(&sprites, sprite_count);
                freepixelformat(&(level.pixelformat));
                return retval;
            }

            if (NEWLEVEL_FLAG) {
                break;
            }
            if (RESETLEVEL_FLAG == 1) {
                if (level.lives == 0) {
                    GAMEOVER_FLAG = true;
                } else {
                    level.lives--;
                    death(&context, &level);
                }
            }




            if (GAMEOVER_FLAG) {
                gameover(&context, &level);

                freelevel (&level);
                freeobjects(&objects, object_count);
                freespritecache(&spritecache);
                freesprites(&sprites, sprite_count);
                freepixelformat(&(level.pixelformat));
                return 0;
            }
            /*
            if (level.player.globalstatus == PLAYER_GLOBAL_STATUS_DEAD) {
                if (level.lives > 0) {
                    level.player.globalstatus = PLAYER_GLOBAL_STATUS_GAMEOVER;
                } else {
                    level.lives--;
                }
            }

            if (level.player.globalstatus == PLAYER_GLOBAL_STATUS_GAMEOVER) {
            }
            */

        }

        freelevel (&level);

        if (retval < 0) {
            freeobjects(&objects, object_count);
            freespritecache(&spritecache);
            freesprites(&sprites, sprite_count);
            freepixelformat(&(level.pixelformat));
            return retval;
        }

    }
    freeobjects(&objects, object_count);
    freespritecache(&spritecache);
    freesprites(&sprites, sprite_count);
    freepixelformat(&(level.pixelformat));
    if (game == Titus) {
        retval = viewimage(titusfinishfile, titusfinishformat, 1, 0);
        if (retval < 0)
            return retval;
    }

    return (0);
}


static int playlevel(ScreenContext *context, TITUS_level *level) {
    int retval = 0;
    bool firstrun = true;
    do {
        if (!firstrun) {
            draw_health_bars(level);
            RETURN_MUSIC(); //Restart music if the song is finished
            flip_screen(context, true);
        }
        firstrun = false;
        IMAGE_COUNTER = (IMAGE_COUNTER + 1) & 0x0FFF; //Cycle from 0 to 0x0FFF
        MOVE_TRP(level); //Move elevators
        move_objects(level); //Object gravity
        retval = move_player(context, level); //Key input, update and move player, handle carried object and decrease timers
        if (retval == TITUS_ERROR_QUIT) {
            return retval;
        }
        MOVE_NMI(level); //Move enemies
        MOVE_TRASH(level); //Move enemy throwed objects
        SET_NMI(level); //Handle enemies on the screen
        CROSSING_GATE(context, level); //Check and handle level completion, and if the player does a kneestand on a secret entrance
        SPRITES_ANIMATION(level); //Animate player and objects
        scroll(level); //X- and Y-scrolling
        DISPLAY_TILES(level); //Draws tiles on the backbuffer
        DISPLAY_SPRITES(level); //Draws sprites on the backbuffer
        retval = RESET_LEVEL(context, level); //Check terminate flags (finishlevel, gameover, death or theend)
        if (retval < 0) {
            return retval;
        }
    } while (retval == 0); //Exits the game loop if the previous function wants to
    return (0);
}

void death(ScreenContext *context, TITUS_level *level) {
    TITUS_player *player = &(level->player);
    int i;

    SELECT_MUSIC(1);
    FORCE_POSE(level);
    updatesprite(level, &(player->sprite), 13, true); //Death
    player->sprite.speedY = 15;
    for (i = 0; i < 60; i++) {
        DISPLAY_TILES(level);
        //TODO! GRAVITY();
        DISPLAY_SPRITES(level);
        flip_screen(context, true);
        player->sprite.speedY--;
        if (player->sprite.speedY < -16) {
            player->sprite.speedY = -16;
        }
        player->sprite.y -= player->sprite.speedY;
    }

    WAIT_SONG();
    SELECT_MUSIC(0);

    /* TODO: remove because REPLACED
    SCREEN_1();
    //TODO: SELECT_MUSIC(LEVEL_MUSIC[FNAMEB]);
    INIT_SCREENM(level);
    return 3; //Do not break main loop
    */
    CLOSE_SCREEN(context);
}

void gameover(ScreenContext *context, TITUS_level *level) {
    TITUS_player *player = &(level->player);
    int i, retval;
    SELECT_MUSIC(2);
    updatesprite(level, &(player->sprite), 13, true); //Death
    updatesprite(level, &(player->sprite2), 333, true); //Game
    player->sprite2.x = (BITMAP_X << 4) - (120-2);
    player->sprite2.y = (BITMAP_Y << 4) + 100;
    //over
    updatesprite(level, &(player->sprite3), 334, true); //Over
    player->sprite3.x = (BITMAP_X << 4) + (320+120-2);
    player->sprite3.y = (BITMAP_Y << 4) + 100;
    for (i = 0; i < 31; i++) {
        DISPLAY_TILES(level);
        DISPLAY_SPRITES(level);
        flip_screen(context, true);
        player->sprite2.x += 8;
        player->sprite3.x -= 8;
    }
    // SCREEN_5C(); //Secret: display picture if LCtrl+LAlt+E is pressed
    retval = waitforbutton();
    if (retval < 0)
        return;

    fadeout();
}

/*
void SCREEN_5C() {
    uint16_t key;
    int retval;
    if (keystate[SDLK_LCTRL] && keystate[SDLK_LALT] && keystate[SDLK_e]) {
        for (key = SDLK_FIRST; key <= SDLK_LAST; key++) {
            if (key == SDLK_LCTRL) continue;
            if (key == SDLK_LALT) continue;
            if (key == SDLK_e) continue;
            if (keystate[key]) return;
        }
        if (game == 0) {
            retval = viewimage(titusfinishfile, titusfinishformat, 1, 0);
            if (retval < 0)
                return;
        }
        SELECT_MUSIC(9);
    }
}
*/
