//
// Created by ricka on 8/16/26.
//

#include "scene_loader.hpp"

#include <nlohmann/json.hpp>
#include <noi_engine/core/resources/resource_system.hpp>

using json = nlohmann::json;

static auto load_resources(noi_engine::resource_system* resources,
						   const json& scene_resources);

namespace noi_engine
{
	auto scene_loader::load(resource_system* resources,
							const std::span<const std::byte> data)
		-> std::unique_ptr<scene>
	{
		auto j = json::parse(data.begin(), data.end());
		auto loaded_scene = std::make_unique<scene>(j["name"]);
		return loaded_scene;
	}
}  // namespace noi_engine

static auto load_resources(noi_engine::resource_system* resources,
						   const json& scene_resources)
{
	if (scene_resources.contains("shaders"))
	{
		for (const auto& shader : scene_resources["shaders"])
		{
			resources->load_shader(shader["name"].get<std::string>(),
								   shader["path"].get<std::string>());
		}
	}

	if (scene_resources.contains("textures"))
	{
		for (const auto& texture : scene_resources["textures"])
		{
			resources->load_texture(texture["name"].get<std::string>(),
									texture["path"].get<std::string>());
		}
	}
}
