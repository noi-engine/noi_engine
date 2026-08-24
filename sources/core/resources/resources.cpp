//
// Created by ricka on 8/23/26.
//

#include <noi_engine/core/resources/resources.hpp>
#include <noi_engine/core/model/shader.hpp>

#include "source_loader/builtin_shaders.hpp"
#include "source_loader/builtin_meshes.hpp"
#include "source_loader/builtin_materials.hpp"

noi_engine::resources::resources(std::unique_ptr<resource_loader> resource_loader) :
    m_resource_loader(std::move(resource_loader))
{
    this->load_from_path<mesh>(NOI_ENGINE_BUILTIN_QUAD_2D_MESH_NAME, NOI_ENGINE_BUILTIN_QUAD_2D_MESH_NAME);
    this->load_from_path<shader>(NOI_ENGINE_BUILTIN_COLOR_SHADER_NAME, NOI_ENGINE_BUILTIN_COLOR_SHADER_NAME);
    this->load_from_path<shader>(NOI_ENGINE_BUILTIN_TEXTURE_SHADER_NAME, NOI_ENGINE_BUILTIN_TEXTURE_SHADER_NAME);
    this->load_from_path<material>(NOI_ENGINE_BUILTIN_COLOR_MATERIAL_NAME, NOI_ENGINE_BUILTIN_COLOR_MATERIAL_NAME);
    this->load_from_path<material>(NOI_ENGINE_BUILTIN_TEXTURE_MATERIAL_NAME, NOI_ENGINE_BUILTIN_TEXTURE_MATERIAL_NAME);
}

auto noi_engine::resources::load_scene(const std::string_view path) -> std::unique_ptr<scene>
{
    return m_resource_loader->load_scene(path, this);
}
