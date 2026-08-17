//
// Created by ricka on 8/17/26.
//

#include "color_parser.hpp"

#include <string>

auto noi_engine::color_parser::parse(std::string_view value) -> glm::vec4
{
    if (!value.empty() && value[0] == '#')
    {
        value = value.substr(1);
    }

    const unsigned long hex_value = std::stoul(std::string(value), nullptr, 16);

    if (value.length() == 8)
    {
        return glm::vec4(
            ((hex_value >> 24) & 0xFF) / 255.0f,
            ((hex_value >> 16) & 0xFF) / 255.0f,
            ((hex_value >> 8) & 0xFF) / 255.0f,
            ((hex_value) & 0xFF) / 255.0f
        );
    }

    return glm::vec4(
        ((hex_value >> 16) & 0xFF) / 255.0f,
        ((hex_value >> 8) & 0xFF) / 255.0f,
        ((hex_value) & 0xFF) / 255.0f,
        1.0f
    );
}
