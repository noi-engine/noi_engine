//
// Created by ricka on 8/16/26.
//

#pragma once

#include <memory>
#include <noi_engine/core/model/shader.hpp>
#include <noi_engine/core/assets/asset_provider.hpp>
#include <span>

namespace noi_engine
{
	class shader_loader
	{
	public:
		shader_loader() = delete;

		[[nodiscard]] static auto load(
			const std::shared_ptr<asset_provider> &asset_provider, std::span<const std::byte> data)
			-> std::unique_ptr<shader>;
	};
}  // namespace noi_engine