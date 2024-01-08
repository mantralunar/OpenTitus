const std = @import("std");

const c = @import("../c.zig");
const window = @import("../window.zig");
const keyboard = @import("../keyboard.zig");
const fonts = @import("fonts.zig");
const globals = @import("../globals.zig");
const g = @import("../game.zig");
const settings = @import("../settings.zig");

pub export fn view_password(game: c.GameType, level: *c.TITUS_level, level_index: u8) c_int {
    var tmpchars: [10]u8 = .{};
    var retval: c_int = undefined;

    window.window_clear(null);
    window.window_render();

    // FIXME: this should not be necessary
    var saved_value = globals.g_scroll_px_offset;
    globals.g_scroll_px_offset = 0;

    if (game == c.Titus) {
        fonts.text_render("Level", 13 * 8, 13 * 8, false);
    } else if (game == c.Moktar) {
        fonts.text_render("Etape", 13 * 8, 13 * 8, false);
    }

    var level_index_ = std.fmt.bufPrint(&tmpchars, "{d}", .{level_index + 1}) catch {
        unreachable;
    };
    var level_index_width = fonts.text_width(level_index_, true);
    fonts.text_render(level_index_, 25 * 8 - level_index_width, 13 * 8, false);

    fonts.text_render("Unlocked!", 14 * 8, 10 * 8, false);
    settings.game_unlock_level(level_index, level.lives);

    window.window_render();
    retval = keyboard.waitforbutton();
    globals.g_scroll_px_offset = saved_value;
    if (retval < 0)
        return retval;

    return (0);
}
