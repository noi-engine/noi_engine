//
// Created by ricka on 8/17/26.
//

#pragma once

#include <string_view>
#include <glm/vec4.hpp>

namespace noi_engine::color_parser
{
    [[nodiscard]] auto parse(std::string_view value) -> glm::vec4;
}