//
// Created by ricka on 8/16/26.
//

#include "scene_loader.hpp"

#include <nlohmann/json.hpp>

using json = nlohmann::json;

namespace noi_engine
{
	auto scene_loader::load(const std::span<const std::byte> data)
		-> std::unique_ptr<scene>
	{
		try
		{
			auto j = json::parse(data.begin(), data.end());

			auto loaded_scene = std::make_unique<scene>(j["name"]);

			return loaded_scene;
		}
		catch (const json::parse_error& e)
		{
			return nullptr;
		}
	}
}  // namespace noi_engine
