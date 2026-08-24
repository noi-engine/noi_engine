//
// Created by ricka on 8/17/26.
//

#include <fstream>
#include <stdexcept>
#include <utility>
#include <noi_engine/core/resources/resource_loader.hpp>

#include "builtin_materials.hpp"
#include "builtin_meshes.hpp"
#include "builtin_shaders.hpp"
#include "loader/mesh_loader.hpp"
#include "loader/shader_loader.hpp"
#include "loader/texture_loader.hpp"
#include "loader/mesh_2d_loader.hpp"
#include "loader/scene_loader.hpp"

namespace noi_engine
{
    source_resource_loader::source_resource_loader(std::filesystem::path root) : m_root(std::move(root))
    {
    }

    auto source_resource_loader::load(const std::string_view path) -> std::vector<std::byte>
    {
        const auto file_path = m_root / path;

        std::ifstream file(file_path, std::ios::binary | std::ios::ate);
        if (!file)
        {
            throw std::runtime_error("Cannot open asset: " + file_path.string());
        }

        const auto size = file.tellg();
        std::vector<std::byte> buffer(size);

        file.seekg(0);
        file.read(reinterpret_cast<char*>(buffer.data()), size);

        return buffer;
    }

    auto source_resource_loader::load_obj(const std::string_view path,
                                          [[maybe_unused]] resources* resources) -> std::unique_ptr<mesh>
    {
        return mesh_loader::load(this->load(path));
    }

    auto source_resource_loader::load_scene(const std::string_view path, resources* resources) -> std::unique_ptr<scene>
    {
        return scene_loader::load(resources, this->load(path));
    }

    auto source_resource_loader::load_mesh_2d(const std::string_view path,
                                              resources* resources) -> std::unique_ptr<mesh>
    {
        if (auto builtin_shader = builtin_meshes::load(path, resources))
        {
            return builtin_shader;
        }
        return mesh_2d_loader::load(this->load(path));
    }

    auto source_resource_loader::load_shader(const std::string_view path,
                                             resources* resources) -> std::unique_ptr<shader>
    {
        if (auto builtin_shader = builtin_shaders::load(path, resources))
        {
            return builtin_shader;
        }

        return shader_loader::load(this, this->load(path));
    }

    auto source_resource_loader::load_texture(const std::string_view path,
                                              [[maybe_unused]] resources* resources) -> std::unique_ptr<texture>
    {
        return texture_loader::load(this->load(path));
    }

    auto source_resource_loader::load_material(std::string_view path, resources* resources) -> std::unique_ptr<material>
    {
        return builtin_materials::load(path, resources);
    }
}
