//
// Created by ricka on 2026-09-04.
//

#pragma once

#include <noi_engine/core/system.hpp>

namespace sandbox
{
    class fps_counter_system : public noi_engine::system
    {
        float m_elapsed{ 0.0f };
        int m_frames{ 0 };

    public:
        auto on_update(const noi_engine::script_context& ctx, float dt) -> void override;

        [[nodiscard]] auto name() const -> std::string_view override { return "fps_counter_system"; }
    };
}  // namespace sandbox
