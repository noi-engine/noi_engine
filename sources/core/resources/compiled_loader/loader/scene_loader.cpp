//
// Created by ricka on 8/18/26.
//

#include "scene_loader.hpp"
#include "fbs/scene_generated.h"
#include "scene_parser/scene_parser.hpp"

auto noi_engine::c::scene_loader::load(resources* resources,
                                       const std::span<const std::byte> data) -> std::unique_ptr<scene>
{
    const auto fbs = fbs::GetScene(data.data());

    const scene_parser parser(resources);

    return parser.parse(fbs);
}
