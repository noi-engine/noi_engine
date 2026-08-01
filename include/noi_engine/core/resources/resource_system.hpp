//
// Created by ricka on 8/1/26.
//

#pragma once

#include <noi_engine/core/resources/resource_manager.hpp>
#include <noi_engine/core/model/mesh.hpp>
#include <noi_engine/core/model/texture.hpp>
#include <noi_engine/core/model/material.hpp>
#include <noi_engine/core/model/shader.hpp>

namespace noi_engine
{
    class resource_system
    {
    public:
        resource_manager<shader> shaders{};
        resource_manager<mesh> meshes{};
        resource_manager<texture> textures{};
        resource_manager<material> materials{};

        resource_system() = default;

        template <typename T>
        [[nodiscard]] auto add(T resource) -> resource_handle<T>;
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
