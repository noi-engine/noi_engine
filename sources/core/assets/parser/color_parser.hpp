//
// Created by ricka on 8/17/26.
//

#pragma once

#include <string_view>
#include <glm/vec4.hpp>

namespace noi_engine
{
    class color_parser
    {
    public:
        color_parser() = delete;

        [[nodiscard]] static auto parse(std::string_view value) -> glm::vec4;
    };
}