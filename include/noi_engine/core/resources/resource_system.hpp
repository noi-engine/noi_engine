//
// Created by ricka on 8/1/26.
//

#pragma once

#include <memory>
#include <noi_engine/core/resources/resource_manager.hpp>
#include <noi_engine/core/model/mesh.hpp>
#include <noi_engine/core/model/texture.hpp>
#include <noi_engine/core/model/material.hpp>
#include <noi_engine/core/model/shader.hpp>
#include <noi_engine/core/assets/asset_provider.hpp>

namespace noi_engine
{
    class resource_system
    {
        std::unique_ptr<asset_provider> m_asset_provider;

    public:
        resource_manager<mesh> meshes{};
        resource_manager<shader> shaders{};
        resource_manager<texture> textures{};
        resource_manager<material> materials{};

        explicit resource_system(std::unique_ptr<asset_provider> assets);

        template <typename T>
        [[nodiscard]] auto add(T resource) -> resource_handle<T>;

        [[nodiscard]] auto add_texture(std::string_view path) -> resource_handle<texture>;
        [[nodiscard]] auto add_mesh(std::string_view path) -> resource_handle<mesh>;
    };

    template <>
    inline auto resource_system::add(shader resource)
        -> resource_handle<shader>
    {
        return shaders.create(std::move(resource));
    }

    template <>
    inline auto resource_system::add(mesh resource)
        -> resource_handle<mesh>
    {
        return meshes.create(std::move(resource));
    }

    template <>
    inline auto resource_system::add(texture resource)
        -> resource_handle<texture>
    {
        return textures.create(std::move(resource));
    }

    template <>
    inline auto resource_system::add(material resource)
        -> resource_handle<material>
    {
        return materials.create(std::move(resource));
    }
}
