//
// Created by ricka on 8/16/26.
//

#pragma once

#include <memory>
#include <noi_engine/core/scene.hpp>
#include <span>

namespace noi_engine
{
	class resource_system;

	class scene_loader
	{
	public:
		scene_loader() = delete;

		[[nodiscard]] static auto load(resource_system* resources, std::span<const std::byte> data)
			-> std::unique_ptr<scene>;
	};
}  // namespace noi_engine