//
// Created by ricka on 8/9/26.
//

#pragma once

#include <cstdint>

namespace noi_engine
{
    enum class key_code : uint16_t
    {
        unknown = 0,

        a = 4, b = 5, c = 6, d = 7, e = 8, f = 9, g = 10, h = 11, i = 12,
        j = 13, k = 14, l = 15, m = 16, n = 17, o = 18, p = 19, q = 20,
        r = 21, s = 22, t = 23, u = 24, v = 25, w = 26, x = 27, y = 28, z = 29,

        num_1 = 30, num_2 = 31, num_3 = 32, num_4 = 33, num_5 = 34,
        num_6 = 35, num_7 = 36, num_8 = 37, num_9 = 38, num_0 = 39,

        return_key = 40,
        escape = 41,
        backspace = 42,
        tab = 43,
        space = 44,

        f1 = 58, f2 = 59, f3 = 60, f4 = 61, f5 = 62, f6 = 63,
        f7 = 64, f8 = 65, f9 = 66, f10 = 67, f11 = 68, f12 = 69,

        right = 79,
        left = 80,
        down = 81,
        up = 82,

        lctrl = 224, lshift = 225, lalt = 226,
        rctrl = 228, rshift = 229, ralt = 230,

        max_keys = 512
    };

    enum class mouse_button : uint8_t
    {
        unknown = 0,
        left = 1,
        middle = 2,
        right = 3,
        x1 = 4,
        x2 = 5,

        max_buttons = 8
    };
}