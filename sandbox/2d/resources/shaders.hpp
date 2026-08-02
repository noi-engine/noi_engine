//
// Created by ricka on 8/2/26.
//

#pragma once

#include <noi_engine/core/model/shader.hpp>

namespace sandbox::twod::shaders
{
    auto color_shader() -> noi_engine::shader;
    auto texture_shader() -> noi_engine::shader;
}
