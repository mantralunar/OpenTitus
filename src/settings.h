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

/* settings.h
 * Handles settings loaded from titus.conf
 */
#pragma once

#include <stdint.h>

int readconfig(const char *configfile);

int initcodes();

enum GameType {
    Titus,
    Moktar
};

extern char spritefile[256];
extern char levelfiles[16][256]; //16 levels in moktar, 15 levels in titus
extern char tituslogofile[256];
extern int tituslogoformat;
extern char titusintrofile[256];
extern int titusintroformat;
extern char titusmenufile[256];
extern int titusmenuformat;
extern char titusfinishfile[256];
extern int titusfinishformat;
extern char fontfile[256];
extern uint16_t levelcount;
extern int devmode;
extern int videomode;
extern enum GameType game;

extern char levelcode[16][5];
