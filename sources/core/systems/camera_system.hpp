//
// Created by ricka on 2026-09-04.
//

#pragma once

#include <noi_engine/core/system.hpp>

namespace noi_engine
{
	class camera_system : public system
	{
	public:
		auto on_update(const script_context& ctx, float dt) -> void override;

		[[nodiscard]] auto name() const -> std::string_view override { return "camera_system"; }
	};
}  // namespace noi_engine
