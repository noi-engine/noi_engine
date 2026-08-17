//
// Created by ricka on 8/17/26.
//

#include "scene_loader.hpp"

#include <nlohmann/json.hpp>
#include <noi_engine/core/resources/resources.hpp>

#include "scene_parser/scene_parser.hpp"

namespace noi_engine
{
    auto scene_loader::load(resources* resources, const std::span<const std::byte> data)
        -> std::unique_ptr<scene>
    {
        const auto root_json = nlohmann::json::parse(data.begin(), data.end());
        const scene_parser parser(resources);
        return parser.parse(root_json);
    }
} // namespace noi_engine