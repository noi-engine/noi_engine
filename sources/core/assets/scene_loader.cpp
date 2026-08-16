#include "scene_loader.hpp"

#include <nlohmann/json.hpp>
#include <noi_engine/core/resources/resource_system.hpp>

#include "parser/scene_parser.hpp"

namespace noi_engine
{
    auto scene_loader::load(resource_system* resources, const std::span<const std::byte> data)
        -> std::unique_ptr<scene>
    {
        const auto root_json = nlohmann::json::parse(data.begin(), data.end());
        scene_parser parser(resources);
        return parser.parse(root_json);
    }
} // namespace noi_engine
