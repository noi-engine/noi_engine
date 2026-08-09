//
// Created by ricka on 8/9/26.
//

#pragma once

#include <SDL_events.h>
#include <noi_engine/core/input/input_state.hpp>

namespace noi_engine::sdl_event_processor
{
    auto process(const SDL_Event& event, input_state& input_state) -> void;
}
