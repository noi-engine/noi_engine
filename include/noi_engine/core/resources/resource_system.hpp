//
// Created by ricka on 8/1/26.
//

#pragma once

#include <any>
#include <memory>
#include <noi_engine/core/model/material.hpp>
#include <noi_engine/core/model/mesh.hpp>
#include <noi_engine/core/model/shader.hpp>
#include <noi_engine/core/model/texture.hpp>
#include <noi_engine/core/scripts/script.hpp>
#include <noi_engine/core/resources/resource_loader.hpp>
#include <noi_engine/core/resources/details/resource_manager.hpp>

namespace noi_engine
{
    class resource_system
    {
        std::unique_ptr<resource_loader> m_resource_loader{};
        std::unordered_map<std::string, std::any> m_registry{};
        std::unordered_map<std::string,
                           std::function<std::unique_ptr<script>()>>
        m_script_factories{};

    public:
        details::resource_manager<mesh> meshes{};
        details::resource_manager<script> scripts{};
        details::resource_manager<shader> shaders{};
        details::resource_manager<texture> textures{};
        details::resource_manager<material> materials{};

        resource_system(const resource_system&) = delete;
        auto operator=(const resource_system&) -> resource_system& = delete;

        explicit resource_system(std::unique_ptr<resource_loader> resource_loader) : m_resource_loader(
            std::move(resource_loader))
        {
        }

        template <typename T>
        auto bind(const std::string_view name, resource_handle<T> handle)
            -> void
        {
            m_registry[std::string(name)] = handle;
        }

        template <typename T>
        [[nodiscard]] auto get_handle(std::string_view name) const
            -> resource_handle<T>
        {
            const auto it = m_registry.find(std::string(name));
            if (it != m_registry.end())
            {
                return std::any_cast<resource_handle<T>>(it->second);
            }
            return {};
        }

        template <typename T>
            requires std::derived_from<T, script>
        void register_script(const std::string_view name)
        {
            this->m_script_factories[std::string(name)] = []()
            {
                return std::make_unique<T>();
            };
        }

        template <typename T>
        auto load_instance(const std::string_view name, std::unique_ptr<T> resource)
            -> resource_handle<T>
        {
            const auto handle = this->load_instance<T>(std::move(resource));
            this->bind<T>(name, handle);
            return handle;
        }

        template <typename T>
        auto load_from_path(std::string_view name, std::string_view path) -> resource_handle<T>
        {
            const auto handle = this->get_handle<T>(name);
            this->bind<T>(name, handle);
            return handle;
        }

        template <typename T>
        auto load_from_path(std::string_view path) -> resource_handle<T>;

        template <typename T>
        auto load_instance(std::unique_ptr<T> resource) -> resource_handle<T>;

        auto load_scene(std::string_view path) -> std::unique_ptr<scene>; //TODO: no idea if should be here or not
    };

    template <>
    inline auto resource_system::load_instance(std::unique_ptr<shader> resource)
        -> resource_handle<shader>
    {
        return shaders.create(std::move(resource));
    }

    template <>
    inline auto resource_system::load_instance(std::unique_ptr<mesh> resource)
        -> resource_handle<mesh>
    {
        return meshes.create(std::move(resource));
    }

    template <>
    inline auto resource_system::load_instance(std::unique_ptr<script> resource)
        -> resource_handle<script>
    {
        return scripts.create(std::move(resource));
    }

    template <>
    inline auto resource_system::load_instance(std::unique_ptr<texture> resource)
        -> resource_handle<texture>
    {
        return textures.create(std::move(resource));
    }

    template <>
    inline auto resource_system::load_instance(std::unique_ptr<material> resource)
        -> resource_handle<material>
    {
        return materials.create(std::move(resource));
    }

    template <>
    inline auto resource_system::load_from_path(const std::string_view path) -> resource_handle<texture>
    {
        auto instance = m_resource_loader->load_texture(path, this);
        return this->load_instance(std::move(instance));
    }

    template <>
    inline auto resource_system::load_from_path(const std::string_view path) -> resource_handle<shader>
    {
        auto instance = m_resource_loader->load_shader(path, this);
        return this->load_instance(std::move(instance));
    }

    template <>
    inline auto resource_system::load_from_path(const std::string_view path) -> resource_handle<mesh>
    {
        auto instance = m_resource_loader->load_mesh_2d(path, this); //TODO: maybe load mesh 3d or 2d
        return this->load_instance(std::move(instance));
    }

    template <>
    inline auto resource_system::load_from_path(const std::string_view path) -> resource_handle<script>
    {
        auto instance = this->m_script_factories[std::string(path)]();
        return this->load_instance(std::move(instance));
    }
} // namespace noi_engine
