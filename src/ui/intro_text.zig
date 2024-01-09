//
// Copyright (C) 2008 - 2024 The OpenTitus team
//
// Authors:
// Eirik Stople
// Petr Mrázek
//
// "Titus the Fox: To Marrakech and Back" (1992) and
// "Lagaf': Les Aventures de Moktar - Vol 1: La Zoubida" (1991)
// was developed by, and is probably copyrighted by Titus Software,
// which, according to Wikipedia, stopped buisness in 2005.
//
// OpenTitus is not affiliated with Titus Software.
//
// OpenTitus is  free software; you can redistribute  it and/or modify
// it under the  terms of the GNU General  Public License as published
// by the Free  Software Foundation; either version 3  of the License,
// or (at your option) any later version.
//
// This program is distributed in the hope that it will be useful, but
// WITHOUT  ANY  WARRANTY;  without   even  the  implied  warranty  of
// MERCHANTABILITY or  FITNESS FOR A PARTICULAR PURPOSE.   See the GNU
// General Public License for more details.
//

const std = @import("std");

const c = @import("../c.zig");
const window = @import("../window.zig");
const keyboard = @import("keyboard.zig");
const fonts = @import("fonts.zig");

// TODO: this is a nice throwback in the original game, but maybe we could do something better.
// Like replace the (missing) manual with an intro sequence to give the player some context.
pub fn viewintrotext() c_int {
    var tmpstring: [41]u8 = .{};
    var rawtime = c.time(null);
    var timeinfo = c.localtime(&rawtime);

    var year = std.fmt.bufPrint(&tmpstring, "     You are still playing Moktar in {d} !!", .{timeinfo.*.tm_year + 1900}) catch {
        unreachable;
    };

    fonts.text_render("     YEAAA . . .", 0, 4 * 12, false);
    fonts.text_render(year, 0, 6 * 12, false);
    fonts.text_render("     Programmed in 1991 on AT .286 12MHz.", 0, 11 * 12, false);
    fonts.text_render("              . . . Enjoy Moktar Adventure !!", 0, 13 * 12, false);

    window.window_render();

    var retval = keyboard.waitforbutton();
    if (retval < 0)
        return retval;

    if (retval < 0)
        return retval;

    return (0);
}