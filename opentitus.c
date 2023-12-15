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

/* opentitus.c
 * Main source file
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "SDL2/SDL.h"

#include "audio.h"

#include "tituserror.h"
#include "sqz.h"
#include "settings.h"
#include "sprites.h"
#include "window.h"
#include "viewimage.h"
#include "fonts.h"
#include "menu.h"
#include "engine.h"
#include "original.h"
#include "objects.h"
#include "window.h"

int init() {

    int retval;

    retval = readconfig("game.conf");
    if (retval < 0)
        return retval;

    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_TIMER | SDL_INIT_AUDIO) != 0) {
        printf("Unable to initialize SDL: %s\n", SDL_GetError());
        return TITUS_ERROR_SDL_ERROR;
    }


    retval = window_init();
    if(retval != 0) {
        return retval;
    }

    initaudio();

    initoriginal();

    initcodes();

    initleveltitles();

    loadfonts();

    return 0;

}

int main(int argc, char *argv[]) {

    int retval;
    int state = 1; //View the menu when the main loop starts
    retval = init();
    if (retval < 0)
        state = 0;

    if (state) {
        retval = viewintrotext();
        if (retval < 0)
            state = 0;
    }

    if (state) {
        retval = viewimage(tituslogofile, tituslogoformat, 0, 4000);
        if (retval < 0)
            state = 0;
    }

    SELECT_MUSIC(15);

    if (state) {
        retval = viewimage(titusintrofile, titusintroformat, 0, 6500);
        if (retval < 0)
            state = 0;
    }

    while (state) {
        retval = viewmenu(titusmenufile, titusmenuformat);

        if (retval <= 0)
            state = 0;

        if (state && (retval <= levelcount)) {
            retval = playtitus(retval - 1);
            if (retval < 0)
                state = 0;
        }
    }

    freefonts();

    freeaudio();

    SDL_Quit();

    checkerror();

    if (retval == -1)
        retval = 0;

    return retval;
}

void checkerror(void) {
    printf("%s\n", lasterror);
}

