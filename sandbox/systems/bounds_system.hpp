//
// Created by ricka on 2026-09-04.
//

#pragma once

#include <noi_engine/core/system.hpp>

namespace sandbox
{
    class bounds_system : public noi_engine::system
    {
    public:
        auto on_update(const noi_engine::script_context& ctx, float dt) -> void override;

        [[nodiscard]] auto name() const -> std::string_view override { return "bounds_system"; }
    };
}  // namespace sandbox
