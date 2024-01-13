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

/* original.c
 * Contains data from the original game
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "SDL2/SDL.h"
#include "original.h"
#include "game.h"
#include <assert.h>

SDL_Color orig_palette_level_colour[16];

uint8_t spritewidth[SPRITECOUNT];
uint8_t spriteheight[SPRITECOUNT];
uint8_t spritecollwidth[SPRITECOUNT];
uint8_t spritecollheight[SPRITECOUNT];
uint8_t spriterefwidth[SPRITECOUNT];
uint8_t spriterefheight[SPRITECOUNT];

int16_t anim_player[ANIM_PLAYER_COUNT][ANIM_PLAYER_MAX];
int16_t anim_enemy[NMI_ANIM_TABLE_COUNT];
uint8_t NMI_POWER[ORIG_LEVEL_COUNT];
uint8_t LEVEL_MUSIC[ORIG_LEVEL_COUNT];

int16_t anim_zoubida[ORIG_ANIM_MAX];
int16_t anim_moktar[ORIG_ANIM_MAX];
int16_t anim_smoke[ORIG_ANIM_MAX];
int16_t COEUR_POS[ORIG_ANIM_MAX * 2];

void initoriginal() {
    int i, j;

    //anim_player --> ACTION
    int16_t orig_anim_player[ANIM_PLAYER_COUNT][ANIM_PLAYER_MAX] = {  {0,-2},
                                    {-1},
                                    {9,8,-4},
                                    {5,6,6,7,7,-8},
                                    {4,-2},
                                    {5,-2},
                                    {11,11,12,12,-8},
                                    {22,-2},
                                    {22,-2},
                                    {9,-2},
                                    {8,8,9,9,-8},
                                    {25,26,27,-6},
                                    {15,15,15,15,15,15,15,15,10,-2},
                                    {28,28,28,28,28,28,28,28,10,-2},
                                    {-1},
                                    {-1},
                                    {16,-2},
                                    {17,17,17,18,18,18,18,19,19,19,18,18,18,18,-28},
                                    {20,21,-4},
                                    {17,17,17,18,18,18,18,19,19,19,18,18,18,18,-28},
                                    {16,-2},
                                    {22,-2},
                                    {23,23,24,24,-8},
                                    {22,-2},
                                    {22,-2},
                                    {-1},
                                    {-1},
                                    {25,26,27,-6},
                                    {15,15,15,15,15,15,15,15,10,-2},
                                    {28,28,28,28,28,28,28,28,10,-2} };

    int16_t anim_zoubida_data[] = {337,337,337,338,338,338,339,339,339,340,340,340,341,341,341,342,342,342,-18*2};
    int16_t anim_moktar_data[] = {343,343,343,344,344,344,345,345,345,-9*2};
    int16_t anim_smoke_data[] = {347,347,348,348,349,349,350,350,351,351,352,352,353,353,354,354,-16*2};

    int16_t COEUR_POS_data[] = {153,142,153,142,153,142,
                        139,148,139,148,139,148,
                        139,162,139,162,139,162,
                        152,171,152,171,152,171,
                        171,165,171,165,171,165,
                        170,147,170,147,170,147,-12*3};

    uint8_t spritewidth_titus[] = {32, 32, 24, 24, 32, 32, 32, 32, 32, 32, 24, 24, 24, 32, 32, 32, 24,
                                24, 24, 32, 24, 24, 24, 32, 32, 32, 32, 32, 32, 32, 24, 24, 16, 16,
                                24, 16, 16, 8, 16, 16, 16, 24, 16, 24, 8, 24, 16, 16, 16, 32, 48,
                                40, 40, 32, 16, 16, 40, 32, 24, 8, 16, 32, 24, 24, 32, 24, 32, 32,
                                16, 24, 16, 32, 32, 16, 16, 32, 32, 32, 32, 24, 16, 24, 32, 32, 40,
                                16, 16, 16, 16, 24, 16, 16, 32, 32, 32, 16, 32, 48, 16, 16, 16, 40,
                                32, 24, 32, 40, 48, 48, 48, 48, 32, 32, 24, 24, 40, 40, 40, 40, 40,
                                40, 40, 24, 24, 56, 32, 56, 24, 24, 24, 32, 24, 32, 32, 32, 40, 40,
                                40, 40, 32, 32, 40, 40, 32, 40, 32, 32, 32, 32, 40, 40, 40, 32, 24,
                                24, 24, 24, 24, 40, 32, 32, 32, 32, 32, 32, 56, 32, 40, 32, 16, 16,
                                16, 16, 32, 32, 32, 32, 32, 32, 32, 32, 40, 32, 40, 40, 40, 32, 32,
                                32, 32, 32, 32, 32, 32, 56, 32, 40, 48, 32, 32, 24, 32, 32, 32, 32,
                                40, 40, 40, 24, 24, 32, 32, 40, 32, 32, 24, 24, 24, 32, 40, 48, 48,
                                32, 32, 40, 40, 48, 40, 32, 32, 40, 40, 40, 32, 32, 40, 32, 24, 40,
                                32, 40, 40, 32, 16, 16, 24, 40, 40, 32, 40, 40, 64, 64, 64, 48, 48,
                                48, 48, 56, 48, 72, 48, 56, 24, 56, 56, 56, 56, 48, 32, 32, 32, 32,
                                48, 48, 40, 40, 40, 48, 56, 48, 16, 16, 40, 48, 40, 40, 40, 40, 40,
                                32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 24, 32, 24, 24, 40, 24, 32,
                                24, 24, 32, 40, 40, 40, 32, 40, 24, 24, 32, 24, 16, 16, 16, 24, 24,
                                24, 16, 24, 16, 8, 32, 56, 64, 88, 64, 64, 80, 72, 80, 32, 40, 40,
                                40, 40, 40, 32, 24, 32, 40, 16, 24, 24, 24, 32, 32, 40, 32, 16};

    uint8_t spriteheight_titus[] = {31, 32, 32, 32, 31, 26, 15, 16, 32, 32, 31, 32, 32, 29, 28, 32, 31,
                                 32, 32, 32, 31, 32, 29, 32, 32, 32, 32, 32, 32, 31, 30, 23, 16, 16,
                                 20, 16, 14, 16, 16, 15, 21, 10, 9, 4, 6, 17, 5, 7, 5, 9, 8,
                                 5, 5, 17, 11, 16, 32, 32, 12, 8, 9, 21, 11, 17, 16, 20, 25, 22,
                                 23, 17, 9, 13, 24, 11, 21, 19, 16, 15, 15, 30, 25, 21, 17, 22, 8,
                                 29, 8, 7, 7, 29, 9, 15, 9, 23, 8, 23, 21, 33, 12, 12, 13, 32,
                                 33, 32, 33, 30, 33, 33, 40, 33, 33, 32, 33, 32, 33, 33, 33, 31, 35,
                                 32, 40, 25, 27, 35, 61, 29, 19, 16, 20, 20, 20, 27, 28, 32, 32, 19,
                                 21, 19, 25, 25, 28, 36, 35, 36, 35, 32, 32, 40, 32, 16, 37, 30, 29,
                                 30, 18, 17, 19, 21, 21, 41, 42, 41, 41, 41, 41, 50, 40, 36, 15, 9,
                                 14, 11, 7, 9, 10, 18, 27, 27, 27, 27, 14, 22, 27, 33, 24, 18, 35,
                                 38, 37, 38, 37, 38, 31, 23, 31, 31, 28, 49, 49, 49, 34, 35, 35, 29,
                                 31, 33, 31, 33, 31, 33, 39, 26, 41, 34, 11, 16, 30, 32, 35, 28, 19,
                                 11, 26, 26, 35, 26, 27, 17, 17, 26, 25, 20, 26, 26, 26, 26, 39, 38,
                                 38, 37, 37, 37, 24, 40, 30, 38, 30, 24, 50, 54, 59, 49, 55, 50, 61,
                                 48, 42, 52, 46, 47, 52, 52, 33, 61, 59, 60, 60, 58, 35, 35, 35, 39,
                                 45, 43, 23, 40, 41, 40, 52, 31, 16, 16, 51, 53, 55, 55, 56, 55, 56,
                                 39, 36, 38, 38, 37, 38, 38, 39, 36, 54, 54, 53, 54, 53, 32, 32, 31,
                                 32, 31, 27, 37, 38, 38, 15, 49, 38, 41, 37, 41, 15, 16, 16, 21, 24,
                                 21, 21, 30, 25, 9, 21, 101, 99, 78, 69, 45, 41, 55, 41, 33, 30, 33,
                                 35, 34, 33, 34, 34, 34, 34, 10, 14, 19, 24, 26, 28, 32, 33, 9};

    uint8_t spritewidth_moktar[] = {24, 32, 24, 32, 32, 32, 32, 32, 32, 32, 32, 24, 24, 32, 32, 32, 24,
                                 32, 24, 32, 24, 24, 32, 32, 32, 40, 40, 40, 32, 48, 24, 24, 16, 16,
                                 24, 16, 16, 8, 16, 16, 16, 24, 16, 24, 8, 24, 16, 16, 16, 32, 48,
                                 40, 40, 32, 16, 16, 40, 32, 24, 8, 16, 32, 24, 24, 32, 24, 32, 32,
                                 16, 24, 16, 32, 32, 16, 16, 32, 32, 32, 32, 24, 16, 24, 32, 32, 40,
                                 16, 16, 16, 16, 24, 16, 16, 32, 32, 32, 16, 32, 48, 16, 16, 16, 40,
                                 32, 24, 32, 40, 48, 48, 48, 48, 32, 32, 24, 24, 40, 40, 40, 40, 40,
                                 40, 40, 24, 24, 56, 32, 56, 24, 24, 24, 32, 24, 32, 32, 32, 40, 40,
                                 40, 40, 32, 32, 40, 40, 32, 40, 32, 32, 32, 32, 40, 40, 40, 32, 24,
                                 24, 24, 24, 24, 40, 32, 32, 32, 32, 32, 32, 56, 32, 40, 32, 16, 16,
                                 16, 16, 32, 32, 32, 32, 32, 32, 32, 32, 40, 32, 40, 40, 40, 32, 32,
                                 32, 32, 32, 32, 32, 32, 56, 32, 40, 48, 32, 32, 24, 32, 32, 32, 32,
                                 40, 40, 40, 24, 24, 32, 32, 40, 32, 32, 24, 24, 24, 32, 40, 48, 48,
                                 32, 32, 40, 40, 48, 40, 32, 32, 40, 40, 40, 32, 32, 40, 32, 24, 40,
                                 32, 40, 40, 32, 16, 16, 24, 40, 40, 32, 40, 40, 64, 64, 64, 48, 48,
                                 48, 48, 56, 48, 72, 48, 56, 24, 56, 56, 56, 56, 48, 32, 32, 32, 32,
                                 48, 48, 40, 40, 40, 48, 56, 48, 16, 16, 40, 48, 40, 40, 40, 40, 40,
                                 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 24, 32, 24, 24, 40, 24, 32,
                                 24, 24, 32, 40, 40, 40, 32, 40, 24, 24, 32, 24, 16, 16, 16, 24, 24,
                                 24, 16, 24, 16, 8, 32, 56, 64, 88, 64, 64, 80, 72, 80, 32, 40, 48,
                                 40, 40, 40, 32, 32, 40, 40, 16, 24, 24, 24, 32, 32, 40, 32, 16};

    uint8_t spriteheight_moktar[] = {32, 31, 30, 31, 31, 21, 16, 16, 32, 32, 29, 32, 32, 28, 24, 32, 32,
                                  32, 32, 32, 32, 32, 27, 32, 32, 34, 32, 32, 33, 33, 30, 23, 16, 16,
                                  20, 16, 14, 16, 16, 15, 21, 10, 9, 4, 6, 17, 5, 7, 5, 9, 8,
                                  5, 5, 17, 11, 16, 32, 32, 12, 8, 9, 21, 11, 17, 16, 20, 25, 22,
                                  23, 17, 9, 13, 24, 11, 21, 19, 16, 15, 15, 30, 25, 21, 17, 22, 8,
                                  29, 8, 7, 7, 29, 9, 15, 9, 23, 8, 23, 21, 33, 12, 12, 13, 32,
                                  33, 32, 33, 30, 33, 33, 40, 33, 33, 32, 33, 32, 33, 33, 33, 31, 35,
                                  32, 40, 25, 27, 35, 61, 29, 19, 16, 20, 20, 20, 27, 28, 32, 32, 19,
                                  21, 19, 27, 27, 31, 32, 31, 34, 31, 32, 32, 40, 32, 16, 37, 30, 29,
                                  30, 18, 17, 19, 21, 21, 41, 42, 41, 41, 41, 41, 50, 41, 36, 15, 9,
                                  14, 11, 7, 9, 10, 18, 27, 27, 27, 27, 14, 22, 27, 33, 24, 18, 35,
                                  38, 37, 38, 37, 38, 31, 23, 31, 31, 28, 49, 49, 49, 34, 35, 35, 29,
                                  31, 33, 31, 33, 31, 33, 39, 26, 41, 34, 11, 16, 30, 32, 35, 28, 19,
                                  11, 26, 26, 35, 26, 27, 17, 17, 26, 25, 20, 26, 26, 26, 26, 39, 38,
                                  38, 37, 37, 37, 24, 40, 30, 38, 30, 24, 50, 54, 59, 49, 55, 50, 61,
                                  48, 42, 52, 46, 47, 52, 52, 33, 61, 59, 60, 60, 58, 35, 35, 35, 39,
                                  45, 43, 23, 40, 41, 40, 52, 31, 16, 16, 51, 53, 55, 55, 56, 55, 56,
                                  39, 36, 38, 38, 37, 38, 38, 39, 36, 54, 54, 53, 54, 53, 32, 32, 31,
                                  32, 31, 27, 37, 38, 38, 15, 49, 38, 41, 37, 41, 15, 16, 16, 21, 24,
                                  21, 21, 30, 25, 9, 21, 101, 99, 78, 69, 45, 41, 55, 41, 33, 30, 33,
                                  35, 34, 33, 29, 30, 30, 31, 10, 14, 19, 24, 26, 28, 32, 33, 9};


    uint8_t tmpspritecoll_titus[] = { 28,31,29,32,27,32,28,32,30,31,30,26,31,15,31,16,30,32,29,32,27,31,28,32,27,32,31,29,29,28,30,32,28,31,28,32,27,32,28,32,28,31,27,32,27,29,29,32,29,32,31,32,31,32,31,32,30,32,29,31,
                                    27,30,26,23,16,16,16,16,25,20,15,16,12,14,11,16,16,16,15,15,13,21,26,10,15,9,28,4,11,6,25,17,12,5,13,7,14,5,29,9,46,8,44,5,43,5,28,17,16,11,16,16,44,32,30,32,25,12,12,8,13,9,29,21,27,11,20,17,32,16,27,20,29,25,29,22,12,
                                    23,28,17,16,9,30,13,30,24,13,11,13,21,31,19,29,16,29,15,31,15,20,30,16,25,28,21,28,17,29,22,41,8,14,29,16,8,15,7,15,7,25,29,16,9,15,15,32,9,28,23,31,8,15,23,29,21,47,33,14,12,14,12,14,13,
                                    42,32,30,33,28,32,29,33,36,30,45,33,45,33,44,40,48,33,28,33,29,32,27,33,26,32,41,33,42,33,42,33,41,31,41,35,43,32,41,40,26,25,27,27,59,35,30,61,59,29,27,19,27,16,26,20,28,20,28,20,31,27,30,28,32,32,36,32,
                                    41,19,41,21,41,19,29,25,29,25,43,28,36,36,32,35,36,36,32,35,29,32,29,32,30,40,36,32,36,16,43,37,29,30,27,29,26,30,25,18,26,17,25,19,43,21,30,21,29,41,29,42,29,41,31,41,29,41,59,41,28,50,41,40,29,36,15,15,16,9,15,14,16,11,
                                    31,7,29,9,30,10,31,18,31,27,31,27,31,27,31,27,36,14,32,22,41,27,42,33,44,24,28,18,31,35,31,38,31,37,31,38,31,37,31,38,32,31,58,23,31,31,36,31,47,28,28,49,29,49,27,49,28,34,29,35,28,35,29,29,43,31,42,33,42,31,27,33,26,31,
                                    28,33,30,39,41,26,32,41,31,34,27,11,27,16,27,30,29,32,44,35,45,28,47,19,29,11,31,26,43,26,43,35,47,26,36,27,
                                    28,17,28,17,42,26,42,25,36,20,31,26,31,26,41,26,31,26,27,39,43,38,29,38,36,37,43,37,32,37,16,24,16,40,28,30,43,38,42,30,32,24,43,50,41,54,63,59,63,49,62,55,45,50,45,61,47,48,47,42,
                                    58,52,46,46,73,47,44,52,57,52,28,33,57,61,57,59,57,60,57,60,46,58,31,35,31,35,31,35,31,39,47,45,47,43,41,23,41,40,41,41,48,40,58,52,48,31,16,16,15,16,44,51,46,53,
                                    44,55,43,55,44,56,43,55,43,56,29,39,29,36,29,38,29,38,32,37,32,38,32,38,32,39,32,36,28,54,28,54,29,53,27,54,27,53,36,32,28,32,29,31,27,32,26,31,28,27,43,37,43,38,42,38,29,15,44,49,27,38,27,41,29,37,27,41,15,15,16,16,15,16,
                                    28,21,26,24,28,21,13,21,20,30,16,25,12,9,29,21,
                                    60,101,62,99,84,78,63,69,64,45,77,41,73,55,77,41,29,33,42,30,44,33,41,35,43,34,42,33,30,34,28,34,29,34,36,34,13,10,20,14,26,19,27,24,29,26,31,28,36,32,32,33,13,9};

    uint8_t tmpspritecoll_moktar[] = {  16,32,30,31,26,30,30,31,31,31,31,21,31,16,31,16,31,32,16,32,29,29,27,32,27,32,32,28,29,24,31,32,27,32,28,32,26,32,30,32,27,32,26,32,31,27,31,32,30,32,36,34,36,32,36,32,31,33,45,33,
                                    27,30,26,23,16,16,16,16,25,20,15,16,12,14,11,16,16,16,15,15,13,21,26,10,15,9,28,4,11,6,25,17,12,5,13,7,14,5,29,9,46,8,44,5,43,5,28,17,16,11,16,16,44,32,30,32,25,12,12,8,13,9,29,21,27,11,20,17,32,16,27,20,29,25,29,22,12,23,
                                    28,17,16,9,30,13,30,24,13,11,13,21,31,19,29,16,29,15,31,15,20,30,16,25,28,21,28,17,29,22,41,8,14,29,16,8,15,7,15,7,25,29,16,9,15,15,32,9,28,23,31,8,15,23,29,21,47,33,14,12,14,12,14,13,
                                    42,32,30,33,28,32,29,33,36,30,45,33,45,33,44,40,48,33,28,33,29,32,27,33,26,32,41,33,42,33,42,33,41,31,41,35,43,32,41,40,26,25,27,27,59,35,30,61,59,29,27,19,27,16,26,20,28,20,28,20,31,27,30,28,32,32,36,32,
                                    41,19,41,21,41,19,29,27,29,27,44,31,41,32,32,31,41,34,32,31,29,32,29,32,30,40,36,32,36,16,43,37,29,30,27,29,26,30,25,18,26,17,25,19,43,21,30,21,29,41,29,42,29,41,31,41,29,41,59,41,28,50,41,41,29,36,15,15,16,9,15,14,16,11,
                                    31,7,29,9,30,10,31,18,31,27,31,27,31,27,31,27,36,14,32,22,41,27,42,33,44,24,28,18,31,35,31,38,31,37,31,38,31,37,31,38,32,31,58,23,31,31,36,31,47,28,28,49,29,49,27,49,28,34,29,35,28,35,29,29,43,31,42,33,42,31,27,33,26,31,
                                    28,33,30,39,41,26,32,41,31,34,27,11,27,16,27,30,29,32,44,35,45,28,47,19,29,11,31,26,43,26,43,35,47,26,36,27,
                                    28,17,28,17,42,26,42,25,36,20,31,26,31,26,41,26,31,26,27,39,43,38,29,38,36,37,43,37,32,37,16,24,16,40,28,30,43,38,42,30,32,24,43,50,41,54,63,59,63,49,62,55,45,50,45,61,47,48,47,42,
                                    58,52,46,46,73,47,44,52,57,52,28,33,57,61,57,59,57,60,57,60,46,58,31,35,31,35,31,35,31,39,47,45,47,43,41,23,41,40,41,41,48,40,58,52,48,31,16,16,15,16,44,51,46,53,
                                    44,55,43,55,44,56,43,55,43,56,29,39,29,36,29,38,29,38,32,37,32,38,32,38,32,39,32,36,28,54,28,54,29,53,27,54,27,53,36,32,28,32,29,31,27,32,26,31,28,27,43,37,43,38,42,38,29,15,44,49,27,38,27,41,29,37,27,41,15,15,16,16,15,16,
                                    28,21,26,24,28,21,13,21,20,30,16,25,12,9,29,21,
                                    60,101,62,99,84,78,63,69,64,45,77,41,73,55,77,41,29,33,42,30,44,33,41,35,43,34,42,33,31,29,31,30,36,30,41,31,13,10,20,14,26,19,27,24,29,26,31,28,36,32,32,33,13,9};

    uint8_t tmpspriteref_titus[] = { 16,31,16,32,9,32,7,32,16,31,16,26,16,15,16,16,16,32,16,32,12,31,12,32,12,32,16,29,16,28,16,32,9,31,9,32,9,32,12,32,9,31,8,32,12,29,16,32,16,32,16,32,16,32,16,32,16,32,16,31,
                                    12,30,12,23,8,16,8,16,12,20,8,16,8,14,4,16,8,16,8,15,8,21,12,10,8,9,12,4,4,6,12,17,8,5,8,7,8,5,16,9,24,8,20,5,20,5,16,17,8,11,8,16,20,32,15,32,12,12,4,8,8,9,16,21,12,11,12,17,
                                    16,16,12,20,16,25,16,22,8,23,12,17,8,9,16,13,16,24,8,11,8,21,16,19,16,16,16,15,16,15,12,30,8,25,12,21,16,17,16,22,20,8,8,29,8,8,8,7,8,7,12,29,0,0,8,15,0,0,16,23,16,8,8,23,16,21,24,33,8,12,8,12,8,13,
                                    20,32,16,33,12,32,16,33,20,30,24,33,24,33,24,40,24,33,16,33,16,32,12,33,12,32,20,33,20,33,20,33,20,31,20,35,20,32,20,40,12,25,12,27,28,35,16,61,28,29,12,19,12,16,12,20,16,20,12,20,16,27,16,28,16,32,20,32,
                                    20,19,20,21,20,19,16,27,16,27,20,30,20,36,16,35,20,36,16,35,16,32,16,32,16,40,20,32,20,16,20,37,16,30,12,29,12,30,12,18,12,17,12,19,20,21,16,21,16,41,16,42,16,41,16,41,16,41,28,41,16,50,20,41,16,36,8,15,8,9,8,14,8,11,
                                    16,7,16,9,16,10,16,18,16,27,16,27,16,27,16,27,20,14,16,22,20,27,20,33,20,24,16,18,16,35,16,38,16,37,16,38,16,37,16,38,31,26,53,16,30,26,35,26,46,9,16,49,16,49,12,49,16,34,16,35,16,35,16,29,20,31,20,33,20,31,12,33,12,31,
                                    16,33,17,38,28,25,21,25,23,23,11,10,11,15,11,29,17,31,28,34,33,27,33,16,16,10,18,24,23,24,15,33,32,24,27,18,
                                    16,17,16,17,20,26,20,25,20,20,16,26,16,26,20,26,16,26,12,39,20,38,16,38,20,37,20,37,16,37,7,23,7,39,15,29,29,37,29,29,16,23,20,50,20,54,32,59,32,49,32,55,24,50,24,61,24,48,24,42,
                                    28,52,24,46,36,47,24,52,28,52,12,33,28,61,28,59,28,60,28,60,24,58,15,34,15,35,15,36,15,39,24,45,24,43,20,23,20,40,20,41,24,39,31,51,24,31,7,15,8,15,20,51,24,53,
                                    20,55,20,55,20,56,20,55,20,56,16,39,16,36,16,38,16,38,16,37,16,38,16,38,16,39,16,36,16,54,12,54,16,53,12,54,12,53,20,32,12,32,16,31,12,32,12,31,16,27,20,37,20,38,20,38,16,15,20,49,12,38,12,41,16,37,12,41,8,15,8,16,8,16,
                                    12,21,12,24,12,21,8,21,12,30,8,25,4,9,16,21,
                                    28,101,32,99,63,78,44,69,32,45,40,41,36,55,40,41,16,33,20,30,20,33,20,35,20,34,20,33,16,34,12,34,16,34,20,34,8,10,12,14,12,19,12,24,16,26,16,28,20,32,16,33,8,9};

    uint8_t tmpspriteref_moktar[] = {  12,32,16,31,12,30,16,31,16,31,16,21,16,16,16,16,16,32,16,32,16,29,12,32,12,32,16,28,16,24,16,32,12,32,16,32,12,32,16,32,12,32,12,32,16,27,16,32,16,32,20,34,20,32,20,32,16,33,24,33,
                                    12,30,12,23,8,16,8,16,12,20,8,16,8,14,4,16,8,16,8,15,8,21,12,10,8,9,12,4,4,6,12,17,8,5,8,7,8,5,16,9,24,8,20,5,20,5,16,17,8,11,8,16,21,32,16,32,12,12,4,8,8,9,16,21,12,11,12,17,16,
                                    16,12,20,16,25,16,22,8,23,12,17,8,9,16,13,16,24,8,11,8,21,16,19,16,16,16,15,16,15,12,30,8,25,12,21,16,17,16,22,20,8,8,29,8,8,8,7,8,7,12,29,0,0,8,15,0,0,16,23,16,8,8,23,16,21,24,33,8,12,8,12,8,13,
                                    20,32,16,33,12,32,16,33,20,30,24,33,24,33,24,40,24,33,16,33,16,32,12,33,12,32,20,33,20,33,20,33,20,31,20,35,20,32,20,40,11,24,11,26,10,34,18,60,43,26,12,19,12,16,12,20,16,20,12,20,16,26,18,26,18,31,23,25,
                                    20,19,20,21,20,19,16,27,16,27,20,31,20,32,16,31,20,34,16,31,16,32,16,32,16,40,20,32,20,16,20,37,16,30,12,29,12,30,12,18,12,17,12,19,20,21,16,21,16,41,16,42,16,41,16,41,16,41,19,40,16,49,25,40,15,35,8,15,8,9,8,14,8,11,
                                    16,7,16,9,16,10,16,18,16,27,16,27,16,27,16,27,20,14,16,22,20,27,20,33,20,24,16,18,16,35,16,38,16,37,16,38,16,37,16,38,31,26,53,16,30,26,35,26,46,9,16,49,16,49,12,49,16,34,16,35,16,35,16,29,20,31,20,33,20,31,12,33,12,31,
                                    16,33,17,38,28,25,21,25,23,23,11,10,11,15,11,29,17,31,28,34,33,27,33,16,16,10,18,24,23,24,15,33,32,24,27,18,
                                    16,17,16,17,20,26,20,25,20,20,16,26,16,26,20,26,16,26,12,39,20,38,16,38,20,37,20,37,16,37,7,23,7,39,15,29,29,37,29,29,16,23,20,50,20,54,32,59,32,49,32,55,24,50,24,61,24,48,24,42,
                                    28,52,24,46,36,47,24,52,28,52,12,33,28,61,28,59,28,60,28,60,24,58,15,34,15,35,15,36,15,39,24,45,24,43,20,23,20,40,20,41,24,39,31,51,24,31,7,15,8,15,20,51,24,53,
                                    20,55,20,55,20,56,20,55,20,56,16,39,16,36,16,38,16,38,16,37,16,38,16,38,16,39,16,36,16,54,12,54,16,53,12,54,12,53,20,32,12,32,16,31,12,32,12,31,16,27,20,37,20,38,20,38,16,15,20,49,12,38,12,41,16,37,12,41,8,15,8,16,8,16,
                                    12,21,12,24,12,21,8,21,12,30,8,25,4,9,16,21,
                                    7,101,11,98,48,77,33,59,32,45,40,41,36,55,40,41,17,32,17,29,19,32,19,34,17,33,16,32,16,29,16,30,20,30,20,31,8,10,12,14,12,19,12,24,16,26,16,28,20,32,16,33,8,9};

    uint8_t tmpanimnmi[] = {  0x35,0x00,0x36,0x00,0x37,0x00,0xAA,0x55,0xFE,0xFF,0x35,0x00,0x36,0x00,0x37,0x00,0xFA,0xFF,0x8D,0x00,0xFE,0xFF,0x8E,0x00,
                            0x8E,0x00,0x8E,0x00,0x8F,0x00,0x8F,0x00,0x8F,0x00,0x90,0x00,0x90,0x00,0x90,0x00,0x91,0x00,0x91,0x00,0x91,0x00,0xE4,0xFF,
                            0x00,0x00,0x00,0x00,0x00,0x00,0x01,0x00,0x01,0x00,0x01,0x00,0x02,0x00,0x02,0x00,0x02,0x00,0x03,0x00,0x03,0x00,0x03,0x00,
                            0xE8,0xFF,0x22,0x00,0x22,0x00,0x23,0x00,0x23,0x00,0x24,0x00,0x24,0x00,0xF4,0xFF,0x05,0x00,0xFE,0xFF,0x06,0x00,0x06,0x00,
                            0x06,0x00,0x07,0x00,0x07,0x00,0x07,0x00,0x08,0x20,0x0C,0x20,0x0B,0x20,0x08,0x00,0x08,0x00,0xE6,0xFF,0x10,0x00,0xFE,0xFF,
                            0x11,0x00,0x11,0x00,0x11,0x00,0x12,0x00,0x12,0x00,0x12,0x00,0x13,0x20,0x0E,0x20,0x19,0x20,0x13,0x00,0xE8,0xFF,0x2C,0x00,
                            0xFE,0xFF,0x2D,0x00,0x2D,0x00,0x2D,0x00,0x2E,0x00,0x2E,0x00,0x2E,0x00,0x2F,0x20,0x0B,0x20,0x0B,0x20,0x2F,0x00,0x2F,0x00,
                            0xE6,0xFF,0x14,0x00,0xFE,0xFF,0x15,0x00,0x15,0x00,0x15,0x00,0x16,0x00,0x16,0x00,0x16,0x00,0x17,0x00,0x17,0x00,0x17,0x00,
                            0x18,0x00,0x18,0x00,0x18,0x00,0xE4,0xFF,0x1E,0x00,0x1E,0x00,0x1E,0x00,0x1F,0x00,0x1F,0x00,0x1F,0x00,0xF4,0xFF,0x20,0x00,
                            0xFE,0xFF,0x21,0x00,0xFE,0xFF,0x19,0x00,0x19,0x00,0x19,0x00,0x1A,0x00,0x1A,0x00,0x1A,0x00,0xF4,0xFF,0x1B,0x00,0x1B,0x00,
                            0x1B,0x00,0x1C,0x00,0x1C,0x00,0x1C,0x00,0xF4,0xFF,0x19,0x00,0x19,0x00,0x19,0x00,0x1A,0x00,0x1A,0x00,0x1A,0x00,0xF4,0xFF,
                            0x30,0x00,0xFE,0xFF,0x31,0x00,0x31,0x00,0x31,0x00,0x31,0x00,0x32,0x00,0x32,0x00,0x32,0x00,0x33,0x00,0x33,0x00,0x33,0x00,
                            0x34,0x00,0x34,0x00,0x34,0x00,0xEE,0xFF,0x32,0x00,0x32,0x00,0x32,0x00,0x33,0x00,0x33,0x00,0x33,0x00,0x34,0x00,0x34,0x00,
                            0x34,0x20,0xEA,0xFF,0x3A,0x00,0xFE,0xFF,0x3B,0x00,0x3B,0x00,0x3B,0x00,0x3C,0x00,0x3C,0x00,0x3C,0x00,0x3D,0x00,0x3D,0x00,
                            0x3D,0x00,0x3E,0x00,0x3E,0x00,0x3E,0x00,0xE8,0xFF,0x3F,0x00,0x3F,0x00,0x40,0x00,0x40,0x00,0x41,0x00,0x41,0x20,0xF0,0xFF,
                            0x38,0x00,0x39,0x00,0xAA,0x55,0xFE,0xFF,0x38,0x00,0x38,0x00,0x38,0x00,0x39,0x00,0x39,0x00,0x39,0x00,0xF4,0xFF,0x43,0x00,
                            0x44,0x00,0xAA,0x55,0xFE,0xFF,0x43,0x00,0x43,0x00,0x43,0x00,0x44,0x00,0x44,0x00,0x44,0x00,0xF4,0xFF,0x47,0x00,0xFE,0xFF,
                            0x47,0x00,0x47,0x00,0x47,0x00,0x48,0x00,0x48,0x00,0x48,0x00,0xF4,0xFF,0x49,0x00,0x49,0x00,0x4A,0x00,0x4A,0x00,0x4A,0x00,
                            0x4B,0x00,0x4B,0x00,0x4B,0x00,0x4C,0x00,0x4C,0x00,0x4C,0x00,0x4D,0x00,0x4D,0x00,0x4D,0x00,0x4E,0x00,0x4E,0x00,0x4E,0x00,
                            0x4D,0x00,0x4D,0x00,0x4D,0x00,0x4C,0x00,0x4C,0x00,0x4C,0x00,0x4B,0x00,0x4B,0x00,0x4B,0x00,0x4A,0x00,0x4A,0x00,0x4A,0x20,
                            0xB8,0xFF,0x4F,0x00,0x4F,0x00,0x4F,0x00,0x50,0x00,0x50,0x00,0x50,0x00,0x51,0x00,0x51,0x00,0x51,0x00,0x52,0x00,0x52,0x00,
                            0x52,0x00,0x52,0x00,0x52,0x00,0x52,0x00,0x52,0x00,0x51,0x00,0x51,0x00,0x51,0x00,0x50,0x00,0x50,0x00,0x50,0x00,0x4F,0x00,
                            0x4F,0x00,0x4F,0x20,0x84,0xFF,0x82,0xFF,0x80,0xFF,0x25,0x00,0xFE,0xFF,0x26,0x00,0xFE,0xFF,0x27,0x00,0x27,0x00,0x27,0x00,
                            0x28,0x00,0x28,0x00,0x28,0x00,0x29,0x00,0x29,0x00,0x29,0x00,0x2A,0x00,0x2A,0x00,0x2A,0x00,0x2B,0x00,0x2B,0x00,0x2B,0x00,
                            0xE8,0xFF,0x54,0x00,0xAA,0x55,0xFE,0xFF,0x54,0x00,0x54,0x00,0x54,0x00,0x55,0x00,0x55,0x00,0x55,0x00,0x56,0x00,0x56,0x00,
                            0x56,0x00,0x57,0x00,0x57,0x00,0x57,0x00,0x58,0x00,0x58,0x00,0x58,0x00,0x59,0x00,0x59,0x00,0x59,0x00,0x5A,0x00,0x5A,0x00,
                            0x5A,0x00,0xE8,0xFF,0x57,0x00,0x57,0x00,0x57,0x20,0xE6,0xFF,0x83,0x00,0x84,0x00,0x85,0x00,0x86,0x00,0x82,0x00,0xFE,0xFF,
                            0x83,0x00,0xFE,0xFF,0x84,0x00,0x84,0x00,0x85,0x00,0x85,0x00,0x86,0x00,0x86,0x00,0xF4,0xFF,0x7E,0x00,0xFE,0xFF,0x80,0x00,
                            0x80,0x00,0xAD,0x00,0xAD,0x00,0x81,0x00,0x81,0x00,0xF4,0xFF,0x80,0x00,0x80,0x00,0xAD,0x00,0xAD,0x00,0x81,0x00,0x81,0x20,
                            0xF0,0xFF,0x7F,0x00,0x7E,0x00,0xFE,0xFF,0x7F,0x00,0xFE,0xFF,0x80,0x00,0x80,0x00,0xAD,0x00,0xAD,0x00,0x81,0x00,0x81,0x00,
                            0xF4,0xFF,0x80,0x00,0x80,0x00,0xAD,0x00,0xAD,0x00,0x81,0x00,0x81,0x00,0xF4,0xFF,0x78,0x00,0xFE,0xFF,0x78,0x00,0x78,0x00,
                            0x78,0x00,0x78,0x00,0x79,0x00,0x79,0x00,0x79,0x00,0x79,0x00,0x7A,0x00,0x7A,0x00,0x7A,0x00,0x7A,0x00,0x7B,0x00,0x7B,0x00,
                            0x7B,0x00,0x7B,0x00,0x7C,0x00,0x7C,0x20,0x0D,0x20,0x00,0x20,0x7C,0x00,0x7C,0x00,0xD0,0xFF,0xA1,0x00,0xFE,0xFF,0x09,0x00,
                            0x09,0x00,0x09,0x00,0x0A,0x00,0x0A,0x00,0x0A,0x00,0x0B,0x00,0x0B,0x00,0x0B,0x00,0x0C,0x00,0x0C,0x00,0x0C,0x00,0xE8,0xFF,
                            0x0F,0x00,0x0F,0x00,0x0F,0x00,0x0D,0x00,0x0D,0x00,0x0D,0x00,0x0E,0x20,0x1D,0x20,0x10,0x20,0x0E,0x00,0x0E,0x00,0xD0,0xFF,
                            0x67,0x00,0x67,0x00,0x67,0x00,0x68,0x00,0x68,0x00,0x68,0x00,0x69,0x00,0x69,0x00,0x69,0x00,0xEE,0xFF,0x6A,0x00,0x6A,0x00,
                            0x6A,0x00,0x6B,0x00,0x6B,0x00,0x6B,0x00,0x6C,0x00,0x6C,0x00,0x6C,0x00,0xEE,0xFF,0xAB,0x00,0xAB,0x00,0xAC,0x00,0xAC,0x00,
                            0xF8,0xFF,0x71,0x00,0xFE,0xFF,0x72,0x00,0x72,0x00,0x73,0x00,0x73,0x00,0x74,0x00,0x74,0x00,0x75,0x00,0x75,0x00,0x76,0x00,
                            0x76,0x00,0xE8,0xFF,0xA7,0x00,0xA7,0x00,0xA7,0x00,0xA7,0x00,0xA7,0x00,0xA7,0x00,0xA8,0x00,0xA8,0x00,0xA8,0x00,0xA8,0x00,
                            0xA8,0x00,0xA8,0x00,0xA9,0x00,0xA9,0x00,0xA9,0x00,0xA9,0x00,0xA9,0x00,0xA9,0x00,0xA8,0x00,0xA8,0x00,0xA8,0x00,0xA8,0x00,
                            0xA8,0x00,0xA8,0x00,0xD0,0xFF,0xAA,0x00,0xAA,0x00,0xAA,0x20,0x0D,0x20,0x14,0x20,0xAA,0x00,0xAA,0x00,0xC0,0xFF,0xAE,0x00,
                            0xFE,0xFF,0xAF,0x00,0xAF,0x20,0x44,0x20,0x0C,0x20,0xAF,0x00,0xAF,0x00,0xF0,0xFF,0xB0,0x00,0xFE,0xFF,0xB1,0x00,0xB1,0x00,
                            0xB1,0x20,0x0E,0x20,0x10,0x20,0xB1,0x00,0xB1,0x00,0xEE,0xFF,0xB2,0x00,0xAA,0x55,0xFE,0xFF,0xB2,0x00,0xFE,0xFF,0xB3,0x00,
                            0xB3,0x00,0xB3,0x00,0xB4,0x00,0xB4,0x00,0xB4,0x00,0xF4,0xFF,0xB4,0x00,0xFE,0xFF,0xB4,0x00,0xFE,0xFF,0xBC,0x00,0xBC,0x00,
                            0xBC,0x00,0xBD,0x00,0xBD,0x00,0xBD,0x00,0xBE,0x00,0xBE,0x00,0xBE,0x00,0xBF,0x00,0xBF,0x00,0xBF,0x00,0xE8,0xFF,0xC0,0x00,
                            0xC0,0x00,0xC0,0x00,0xC1,0x00,0xC1,0x00,0xC1,0x00,0xC2,0x00,0xC2,0x00,0xC2,0x00,0xC3,0x00,0xC3,0x00,0xC3,0x00,0xC4,0x00,
                            0xC4,0x00,0xC4,0x00,0xE2,0xFF,0x5B,0x00,0x5B,0x00,0x5B,0x00,0x5D,0x00,0x5D,0x00,0x5D,0x00,0xF4,0xFF,0x5E,0x00,0x5E,0x00,
                            0x5E,0x20,0x1E,0x20,0x08,0x20,0x5E,0x00,0x5E,0x00,0x5E,0x00,0x5E,0x00,0x5E,0x00,0x5E,0x00,0x5E,0x00,0x5E,0x00,0x5E,0x00,
                            0x5E,0x00,0x5C,0x00,0x5C,0x00,0x5C,0x00,0x5C,0x00,0x5C,0x00,0xD2,0xFF,0xD3,0x00,0xFE,0xFF,0xD4,0x00,0xD4,0x00,0xD5,0x00,
                            0xD5,0x00,0xD5,0x00,0xD6,0x00,0xD6,0x00,0xD6,0x00,0xD7,0x00,0xD7,0x00,0xD7,0x00,0xD8,0x00,0xD8,0x00,0xD8,0x00,0xE8,0xFF,
                            0xD5,0x00,0xD5,0x00,0xD5,0x00,0xD6,0x00,0xD6,0x00,0xD6,0x00,0xD7,0x00,0xD7,0x00,0xD7,0x00,0xD8,0x00,0xD8,0x00,0xD8,0x20,
                            0xE4,0xFF,0x45,0x00,0x45,0x00,0x45,0x00,0x46,0x00,0x46,0x00,0x46,0x00,0xF4,0xFF,0x45,0x00,0x45,0x00,0x45,0x00,0x46,0x00,
                            0x46,0x00,0x46,0x00,0xF4,0xFF,0x45,0x00,0x45,0x00,0x45,0x00,0x46,0x00,0x46,0x00,0x46,0x00,0xF4,0xFF,0x6D,0x00,0x6E,0x00,
                            0x6F,0x00,0xFE,0xFF,0x6F,0x00,0x6F,0x00,0x6F,0x00,0x6E,0x00,0x6D,0x00,0x6D,0x00,0x6D,0x00,0x6E,0x20,0x1C,0x20,0x10,0x20,
                            0x6E,0x00,0x6E,0x00,0x6F,0x00,0x6F,0x00,0x6F,0x00,0x6F,0x00,0xDC,0xFF,0xDF,0x00,0xFE,0xFF,0x87,0x00,0x87,0x00,0x87,0x00,
                            0x88,0x00,0x88,0x00,0x88,0x00,0x89,0x00,0x89,0x00,0x89,0x00,0xEE,0xFF,0x51,0x20,0xF0,0xFF,0x8A,0x00,0x8A,0x00,0x8A,0x00,
                            0x8B,0x00,0x8B,0x00,0x8B,0x00,0x8C,0x00,0x8C,0x00,0x8C,0x00,0x8B,0x00,0x8B,0x00,0x8B,0x00,0xE8,0xFF,0x51,0x20,0xF2,0xFF,
                            0xB5,0x00,0xB5,0x00,0xB5,0x00,0xB6,0x00,0xB6,0x00,0xB6,0x00,0xF4,0xFF,0x52,0x20,0xF2,0xFF,0xE0,0x00,0xFE,0xFF,0x4F,0x20,
                            0xF8,0xFF,0xE1,0x00,0xFE,0xFF,0x50,0x20,0xF8,0xFF,0xE2,0x00,0xFE,0xFF,0x3B,0x20,0xF8,0xFF,0xE3,0x00,0xFE,0xFF,0xD9,0x00,
                            0xDA,0x00,0xDB,0x00,0xAA,0x55,0xFE,0xFF,0xD9,0x00,0xD9,0x00,0xDA,0x00,0xDA,0x00,0xDB,0x00,0xDB,0x00,0xF4,0xFF,0xDC,0x00,
                            0xDD,0x00,0xDE,0x00,0xAA,0x55,0xFE,0xFF,0xDC,0x00,0xDC,0x00,0xDD,0x00,0xDD,0x00,0xDE,0x00,0xDE,0x00,0xF4,0xFF,0xD0,0x00,
                            0xD0,0x00,0xD0,0x00,0xD1,0x00,0xD1,0x00,0xD1,0x00,0xD2,0x00,0xD2,0x00,0xD2,0x00,0xEE,0xFF,0x93,0x00,0xFE,0xFF,0x94,0x00,
                            0x94,0x00,0x94,0x00,0x94,0x00,0x95,0x00,0x95,0x00,0x95,0x00,0x95,0x00,0x95,0x00,0x95,0x00,0x96,0x20,0x1D,0x20,0x14,0x20,
                            0x96,0x00,0x96,0x00,0xDE,0xFF,0x9C,0x00,0xFE,0xFF,0x9D,0x00,0x9D,0x00,0x9D,0x00,0x9D,0x00,0x9D,0x00,0x9E,0x00,0x9E,0x00,
                            0x9E,0x00,0x9E,0x00,0x9E,0x00,0x9F,0x00,0x9F,0x00,0x9F,0x00,0xA0,0x20,0x3D,0x20,0x04,0x20,0xA0,0x00,0xA0,0x00,0xA0,0x00,
                            0xA0,0x00,0xD4,0xFF,0xB7,0x00,0xB7,0x00,0xB7,0x00,0xFA,0xFF,0xB7,0x00,0xB7,0x00,0xB7,0x00,0xFA,0xFF,0xB8,0x00,0xB8,0x00,
                            0xB8,0x00,0xB9,0x00,0xB9,0x00,0xB9,0x00,0xBA,0x00,0xBA,0x00,0xBA,0x00,0xBB,0x00,0xBB,0x00,0xBB,0x00,0xE8,0xFF,0xA2,0x00,
                            0xFE,0xFF,0xA2,0x00,0xA2,0x00,0xA2,0x00,0xA3,0x00,0xA3,0x00,0xA3,0x00,0xA4,0x00,0xA4,0x00,0xA4,0x00,0xA5,0x00,0xA5,0x00,
                            0xA5,0x00,0xE8,0xFF,0xA2,0x00,0xA2,0x00,0xA2,0x00,0xA3,0x00,0xA3,0x00,0xA3,0x00,0xA4,0x00,0xA4,0x00,0xA4,0x00,0xA5,0x00,
                            0xA5,0x00,0xA5,0x00,0xA6,0x00,0xA6,0x00,0xA6,0x20,0xDE,0xFF,0x97,0x00,0xFE,0xFF,0x98,0x00,0x98,0x00,0x98,0x00,0x99,0x00,
                            0xFE,0xFF,0x9A,0x00,0xFE,0xFF,0x9B,0x00,0xFE,0xFF,0xE4,0x00,0xFE,0xFF,0xE4,0x00,0xE4,0x00,0xE5,0x00,0xE5,0x00,0xF8,0xFF,
                            0xE6,0x00,0xE6,0x00,0xE7,0x00,0xE7,0x00,0xE6,0x00,0xE6,0x20,0xF0,0xFF,0x63,0x00,0x63,0x00,0x63,0x00,0x64,0x00,0x64,0x00,
                            0x64,0x00,0x65,0x00,0x65,0x00,0x65,0x00,0xEE,0xFF,0x60,0x00,0x60,0x00,0x60,0x00,0x61,0x00,0x61,0x00,0x61,0x00,0x62,0x00,
                            0x62,0x00,0x62,0x00,0xEE,0xFF};

    uint8_t tmp_nmi_power[] = {10,10,10,4,10,10,10,10,10,10,0,10,10,6,10,10,10,0,0,10};

    uint8_t tmp_level_music[] = {12,12,13,13,12,11,13,10,3,10,0,11,13,10,11,12,14,0,0,11};

    for (i = 0; i < ORIG_LEVEL_COUNT; i++) {
        LEVEL_MUSIC[i] = tmp_level_music[i];
    }

    for (i = 0; i < ORIG_LEVEL_COUNT; i++) {
        NMI_POWER[i] = tmp_nmi_power[i];
    }

    for (i = 0; i < NMI_ANIM_TABLE_COUNT; i++) {
        uint8_t first = tmpanimnmi[i * 2 + 1];
        uint8_t second = tmpanimnmi[i * 2];
        anim_enemy[i] = (int16_t)(((uint16_t)(first) << 8) + (uint16_t)(second));
    }

    for (i = 0; i < ORIG_ANIM_MAX; i++) {
        anim_zoubida[i] = anim_zoubida_data[i];
        if (anim_zoubida[i] < 0) {
            break;
        }
    }

    for (i = 0; i < ORIG_ANIM_MAX; i++) {
        anim_moktar[i] = anim_moktar_data[i];
        if (anim_moktar[i] < 0) {
            break;
        }
    }

    for (i = 0; i < ORIG_ANIM_MAX; i++) {
        anim_smoke[i] = anim_smoke_data[i];
        if (anim_smoke[i] < 0) {
            break;
        }
    }

    for (i = 0; i < ORIG_ANIM_MAX * 2; i++) {
        COEUR_POS[i] = COEUR_POS_data[i];
        if (COEUR_POS[i] < 0) {
            break;
        }
    }

    for (i = 0; i < ANIM_PLAYER_COUNT; i++) {
        for (j = 0; j < ANIM_PLAYER_MAX; j++) {
            anim_player[i][j] = orig_anim_player[i][j];
            if (anim_player[i][j] < 0) {
                break;
            }
        }
    }

    if (game == Titus) {
        for (i = 0; i < SPRITECOUNT; i++) {
            spritewidth[i] = spritewidth_titus[i];
            spriteheight[i] = spriteheight_titus[i];
            spritecollwidth[i] = tmpspritecoll_titus[i * 2];
            spritecollheight[i] = tmpspritecoll_titus[(i * 2) + 1];
            spriterefwidth[i] = tmpspriteref_titus[i * 2];
            spriterefheight[i] = tmpspriteref_titus[(i * 2) + 1];
        }
        int16_t anim_player_titus[] =     {2,2,2,1,1,1,1,2,2,2,3,3,3,3,-28};
        for (i = 0; i < ANIM_PLAYER_MAX; i++) {
            anim_player[1][i] = anim_player_titus[i];
        }
    } else if (game == Moktar) {
        for (i = 0; i < SPRITECOUNT; i++) {
            spritewidth[i] = spritewidth_moktar[i];
            spriteheight[i] = spriteheight_moktar[i];
            spritecollwidth[i] = tmpspritecoll_moktar[i * 2];
            spritecollheight[i] = tmpspritecoll_moktar[(i * 2) + 1];
            spriterefwidth[i] = tmpspriteref_moktar[i * 2];
            spriterefheight[i] = tmpspriteref_moktar[(i * 2) + 1];
        }
        #define ANIM_PLAYER_MAX_MOKTAR 12
        int16_t anim_player_moktar[] =    {2,2,2,1,1,1,2,2,3,3,3,-11*2};
        for (i = 0; i < ANIM_PLAYER_MAX_MOKTAR; i++) {
            anim_player[1][i] = anim_player_moktar[i];
        }
    }
}

uint16_t getlevelid(uint16_t levelnumber) {
    uint16_t levelid_titus[] = {1,3,4,5,6,7,8,9,10,11,300,12,13,300,14,300,15,300,300,2};
    uint16_t levelid_moktar[] = {1,3,4,5,6,7,8,9,10,11,300,12,13,300,14,15,16,300,300,2};
    uint16_t i;
    if (game == Titus) {
        for (i = 0; i < 20; i++) {
            if (levelid_titus[i] == levelnumber + 1) {
                return i;
            }
        }
    } else {
        for (i = 0; i < 20; i++) {
            if (levelid_moktar[i] == levelnumber + 1) {
                return i;
            }
        }
    }
    assert(false);
    return 65535;
}
