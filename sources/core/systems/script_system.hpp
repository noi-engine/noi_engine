//
// Created by ricka on 8/9/26.
//

#pragma once

#include <noi_engine/core/model/script.hpp>

namespace noi_engine
{
    class script_system
    {
    public:
        script_system() = delete;

        static auto before_update(const script_context& context, float dt) -> void;

        static auto after_render(const script_context& context) -> void;
        static auto before_render(const script_context& context) -> void;
        static auto update(const script_context& context, float dt) -> void;
        static auto after_update(const script_context& context, float dt) -> void;
        static auto destroy(const script_context& context, entity target) -> void;
    };
}
