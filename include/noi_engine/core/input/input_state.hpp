//
// Created by ricka on 8/1/26.
//

#pragma once

namespace noi_engine
{
    struct input_state
    {
        float mouse_delta_x{0.0f};
        float mouse_delta_y{0.0f};
        float scroll_delta{0.0f};
        bool right_mouse_held{false};
        bool left_mouse_held{false};
    };
}
