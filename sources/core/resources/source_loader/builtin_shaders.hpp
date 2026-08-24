//
// Created by ricka on 8/23/26.
//

#pragma once

#include <memory>
#include <noi_engine/core/model/shader.hpp>
#include <noi_engine/core/resources/resources.hpp>

#define NOI_ENGINE_BUILTIN_COLOR_SHADER_NAME "shaders:color"
#define NOI_ENGINE_BUILTIN_TEXTURE_SHADER_NAME "shaders:texture"

namespace noi_engine::builtin_shaders
{
    [[nodiscard]] auto load(std::string_view name, resources* resources) -> std::unique_ptr<shader>;
}
