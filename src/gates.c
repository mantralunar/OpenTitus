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

/* gates.c
 * Handles gates (kneestand) and checks if the player have completed the level
 */

#include <stdio.h>
#include <stdlib.h>
#include "SDL2/SDL.h"
#include "globals_old.h"
#include "window.h"
#include "sprites.h"
#include "settings.h"
#include "audio.h"
#include "gates.h"
#include "scroll.h"
#include "draw.h"

static void check_finish(ScreenContext *context, TITUS_level *level) {
    TITUS_player *player = &(level->player);
    if (boss_alive) { //There is still a boss that needs to be killed!
        return;
    }
    if (level->levelid == 9) { //The level with a cage
        if ((level->player.sprite2.number != FIRST_OBJET + 26) &&
          (level->player.sprite2.number != FIRST_OBJET + 27)) {
            return;
        }
    }
    if (((player->sprite.x & 0xFFF0) != level->finishX) &&
      ((player->sprite.x & 0xFFF0) - 16 != level->finishX)) {
        return;
    }
    if (((player->sprite.y & 0xFFF0) != level->finishY) &&
      ((player->sprite.y & 0xFFF0) - 16 != level->finishY)) {
        return;
    }
    music_select_song(4);
    music_wait_to_finish();
    CLOSE_SCREEN(context);
    NEWLEVEL_FLAG = true;
}

static void check_gates(ScreenContext *context, TITUS_level *level) {
    TITUS_player *player = &(level->player);
    uint8_t i;
    if ((CROSS_FLAG == 0) || //not kneestanding
      (NEWLEVEL_FLAG)) { //the player has finished the level
        return;
    }
    for (i = 0; i < level->gatecount; i++) {
        if ((level->gate[i].exists) &&
          (level->gate[i].entranceX == (player->sprite.x >> 4)) &&
          (level->gate[i].entranceY == (player->sprite.y >> 4))) {
            break;
        }
    }
    if (i == level->gatecount) {
        return; //No matching gate
    }
    player->sprite.speedX = 0;
    player->sprite.speedY = 0;
    CLOSE_SCREEN(context);
    uint16_t orig_xlimit = XLIMIT;
    bool orig_xlimit_breached = XLIMIT_BREACHED;
    XLIMIT = level->width - screen_width;
    player->sprite.x = level->gate[i].exitX << 4;
    player->sprite.y = level->gate[i].exitY << 4;
    while (BITMAP_Y < level->gate[i].screenY) {
        D_SCROLL(level);
    }
    while (BITMAP_Y > level->gate[i].screenY) {
        U_SCROLL(level);
    }
    while (BITMAP_X < level->gate[i].screenX) {
        R_SCROLL(level);
    }
    while (BITMAP_X > level->gate[i].screenX) {
        L_SCROLL(level);
    }
    XLIMIT = orig_xlimit;
    XLIMIT_BREACHED = orig_xlimit_breached;
    NOSCROLL_FLAG = level->gate[i].noscroll;
    OPEN_SCREEN(context, level);
}

void CROSSING_GATE(ScreenContext *context, TITUS_level *level) { //Check and handle level completion, and if the player does a kneestand on a secret entrance
    check_finish(context, level);
    check_gates(context, level);
}

void CLOSE_SCREEN(ScreenContext *context) {
    SDL_Rect dest;
    uint8_t step_count = 10;
    uint16_t rwidth = 320; //TODO: make this global
    uint16_t rheight = 192;
    uint16_t incX = rwidth / (step_count * 2);  //16
    uint16_t incY = rheight / (step_count * 2); //10
    uint8_t i;
    for (i = 0; i < step_count; i++) {
        flip_screen(context, false); //quick flip TODO: move to other end of loop?

        //Clear top
        dest.x = 0;
        dest.y = 0;
        dest.w = screen_width * 16;
        dest.h = i * incY;
        window_clear(&dest);

        //Clear left
        dest.x = 0;
        dest.y = 0;
        dest.w = i * incX;
        dest.h = screen_height * 16;
        window_clear(&dest);

        //Clear bottom
        dest.x = 0;
        dest.y = rheight - (i * incY);
        dest.w = screen_width * 16;
        dest.h = i * incY;
        window_clear(&dest);

        //Clear right
        dest.x = rwidth - (i * incX);
        dest.y = 0;
        dest.w = i * incX;
        dest.h = screen_height * 16;
        window_clear(&dest);
    }
}


void OPEN_SCREEN(ScreenContext *context, TITUS_level *level) {
    SDL_Rect dest;
    int8_t step_count = 10;
    uint16_t rwidth = 320; //TODO: make this global
    uint16_t rheight = 192;
    uint16_t incX = rwidth / (step_count * 2);  //16
    uint16_t incY = rheight / (step_count * 2); //10
    uint8_t i;
    for (i = step_count - 1; i >= 2; i -= 2) {
        flip_screen(context, false); //quick flip TODO: move to other end of loop?

        // draw all tiles
        DISPLAY_TILES(level);

        //Clear top
        dest.x = 0;
        dest.y = 0;
        dest.w = screen_width * 16;
        dest.h = i * incY;
        window_clear(&dest);

        //Clear left
        dest.x = 0;
        dest.y = 0;
        dest.w = i * incX;
        dest.h = screen_height * 16;
        window_clear(&dest);

        //Clear bottom
        dest.x = 0;
        dest.y = rheight - (i * incY);
        dest.w = screen_width * 16;
        dest.h = i * incY;
        window_clear(&dest);

        //Clear right
        dest.x = rwidth - (i * incX);
        dest.y = 0;
        dest.w = i * incX;
        dest.h = screen_height * 16;
        window_clear(&dest);
    }
}
