//
// Created by ricka on 8/17/26.
//

#include <noi_engine/core/resources/resource_loader.hpp>

#include "loader/shader_loader.hpp"
#include "loader/scene_loader.hpp"
#include "loader/mesh_2d_loader.hpp"

namespace noi_engine
{
    compiled_resource_loader::compiled_resource_loader(std::filesystem::path root) : m_root(std::move(root))
    {
        this->m_source_loader = source_resource_loader(this->m_root);
    }

    auto compiled_resource_loader::load(const std::string_view path) -> std::vector<std::byte>
    {
        return this->m_source_loader.load(path);
    }

    auto compiled_resource_loader::load_obj(const std::string_view path, resources* resources) -> std::unique_ptr<mesh>
    {
        return this->m_source_loader.load_obj(path, resources);
    }

    auto compiled_resource_loader::load_scene(const std::string_view path,
                                              resources* resources) -> std::unique_ptr<scene>
    {
        return c::scene_loader::load(resources, this->load(path));
    }

    auto compiled_resource_loader::load_mesh_2d(const std::string_view path,
                                                [[maybe_unused]] resources* resources) -> std::unique_ptr<mesh>
    {
        return c::mesh_2d_loader::load(this->load(path));
    }

    auto compiled_resource_loader::load_shader(const std::string_view path,
                                               [[maybe_unused]] resources* resources) -> std::unique_ptr<shader>
    {
        return c::shader_loader::load(this, this->load(path));
    }

    auto compiled_resource_loader::load_texture(const std::string_view path,
                                                resources* resources) -> std::unique_ptr<texture>
    {
        return this->m_source_loader.load_texture(path, resources);
    }
}
