//
// Created by ricka on 8/23/26.
//

#pragma once

#include <memory>
#include <noi_engine/core/model/material.hpp>
#include <noi_engine/core/resources/resources.hpp>

#define NOI_ENGINE_BUILTIN_COLOR_MATERIAL_NAME "materials:color"
#define NOI_ENGINE_BUILTIN_TEXTURE_MATERIAL_NAME "materials:texture"

namespace noi_engine::builtin_materials
{
    [[nodiscard]] auto load(std::string_view name, resources* resources) -> std::unique_ptr<material>;
}
