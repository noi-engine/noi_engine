//
// Created by ricka on 8/23/26.
//

#include <noi_engine/core/resources/resources.hpp>

noi_engine::resources::resources(std::unique_ptr<resource_loader> resource_loader) :
    m_resource_loader(std::move(resource_loader))
{
}

auto noi_engine::resources::load_scene(const std::string_view path) -> std::unique_ptr<scene>
{
    return m_resource_loader->load_scene(path, this);
}

auto noi_engine::resources::clear() -> void
{
    meshes.clear();
    scripts.clear();
    shaders.clear();
    textures.clear();
    materials.clear();
    m_registry.clear();
}
