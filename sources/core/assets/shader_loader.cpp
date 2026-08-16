//
// Created by ricka on 8/16/26.
//

#include "shader_loader.hpp"

#include <nlohmann/json.hpp>

using json = nlohmann::json;

namespace noi_engine
{
	auto shader_loader::load(
		const std::shared_ptr<asset_provider>& asset_provider,
		std::span<const std::byte> data) -> std::unique_ptr<shader>
	{
		auto j = json::parse(data.begin(), data.end());

		const auto vert_bytes =
			asset_provider->read(j["vertex"].get<std::string>());

		const auto frag_bytes =
			asset_provider->read(j["fragment"].get<std::string>());

		std::string vert_src(reinterpret_cast<const char*>(vert_bytes.data()),
							 vert_bytes.size());
		std::string frag_src(reinterpret_cast<const char*>(frag_bytes.data()),
							 frag_bytes.size());

		return std::make_unique<shader>(vert_src, frag_src);
	}
}  // namespace noi_engine