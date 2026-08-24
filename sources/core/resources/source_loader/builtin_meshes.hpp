//
// Created by ricka on 8/23/26.
//

#pragma once

#include <memory>
#include <noi_engine/core/model/mesh.hpp>
#include <noi_engine/core/resources/resources.hpp>

#define NOI_ENGINE_BUILTIN_QUAD_2D_MESH_NAME "meshes:quad_2d"

namespace noi_engine::builtin_meshes
{
    [[nodiscard]] auto load(std::string_view name, resources* resources) -> std::unique_ptr<mesh>;
}
