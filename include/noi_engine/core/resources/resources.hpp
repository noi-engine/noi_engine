//
// Created by ricka on 8/1/26.
//

#pragma once

#include <memory>
#include <noi_engine/core/model/material.hpp>
#include <noi_engine/core/model/mesh.hpp>
#include <noi_engine/core/model/shader.hpp>
#include <noi_engine/core/model/texture.hpp>
#include <noi_engine/core/model/script.hpp>
#include <noi_engine/core/resources/resource_loader.hpp>
#include <noi_engine/core/resources/details/resource_manager.hpp>

namespace noi_engine
{
    class resources
    {
        std::unique_ptr<resource_loader> m_resource_loader{};

    public:
        details::resource_manager<mesh> meshes{};
        details::resource_manager<script> scripts{};
        details::resource_manager<shader> shaders{};
        details::resource_manager<texture> textures{};
        details::resource_manager<material> materials{};

        resources(const resources&) = delete;
        auto operator=(const resources&) -> resources& = delete;

        explicit resources(std::unique_ptr<resource_loader> resource_loader);

        template <typename T>
        auto bind(std::string_view name, resource_handle<T> handle) -> void;

        template <typename T>
        [[nodiscard]] auto get_handle(std::string_view name) const
            -> resource_handle<T>;

        template <typename T>
        [[nodiscard]] auto get_label(resource_handle<T> handle) const
            -> std::string_view;

        template <typename T>
            requires std::derived_from<T, script>
        void register_script(const std::string_view name)
        {
            details::script_registry::instance().add(name, []()
            {
                return std::make_unique<T>();
            });
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
            const auto handle = this->load_from_path<T>(path);
            this->bind<T>(name, handle);
            return handle;
        }

        template <typename T>
        auto load_from_path(std::string_view path) -> resource_handle<T>;

        template <typename T>
        auto load_instance(std::unique_ptr<T> resource) -> resource_handle<T>;

        auto load_scene(std::string_view path) -> std::unique_ptr<scene>; //TODO: no idea if should be here or not

        auto clear() -> void;
    };

    template <>
    inline auto resources::load_instance(std::unique_ptr<shader> resource)
        -> resource_handle<shader>
    {
        return shaders.create(std::move(resource));
    }

    template <>
    inline auto resources::load_instance(std::unique_ptr<mesh> resource)
        -> resource_handle<mesh>
    {
        return meshes.create(std::move(resource));
    }

    template <>
    inline auto resources::load_instance(std::unique_ptr<script> resource)
        -> resource_handle<script>
    {
        return scripts.create(std::move(resource));
    }

    template <>
    inline auto resources::load_instance(std::unique_ptr<texture> resource)
        -> resource_handle<texture>
    {
        return textures.create(std::move(resource));
    }

    template <>
    inline auto resources::load_instance(std::unique_ptr<material> resource)
        -> resource_handle<material>
    {
        return materials.create(std::move(resource));
    }

    template <>
    inline auto resources::load_from_path(const std::string_view path) -> resource_handle<texture>
    {
        auto instance = m_resource_loader->load_texture(path, this);
        return this->load_instance(std::move(instance));
    }

    template <>
    inline auto resources::load_from_path(const std::string_view path) -> resource_handle<shader>
    {
        auto instance = m_resource_loader->load_shader(path, this);
        return this->load_instance(std::move(instance));
    }

    template <>
    inline auto resources::load_from_path(const std::string_view path) -> resource_handle<mesh>
    {
        auto instance = m_resource_loader->load_mesh_2d(path, this); //TODO: maybe load mesh 3d or 2d
        return this->load_instance(std::move(instance));
    }

    template <>
    inline auto resources::load_from_path(const std::string_view path) -> resource_handle<script>
    {
        auto instance = details::script_registry::instance().factories().at(std::string(path))();
        return this->load_instance(std::move(instance));
    }

    template <>
    inline auto resources::load_from_path(const std::string_view path) -> resource_handle<material>
    {
        auto instance = this->m_resource_loader->load_material(path, this);
        return this->load_instance(std::move(instance));
    }

    template <>
    inline auto resources::bind(const std::string_view name, const resource_handle<mesh> handle) -> void
    {
        meshes.set_label(handle, name);
    }

    template <>
    inline auto resources::bind(const std::string_view name, const resource_handle<script> handle) -> void
    {
        scripts.set_label(handle, name);
    }

    template <>
    inline auto resources::bind(const std::string_view name, const resource_handle<shader> handle) -> void
    {
        shaders.set_label(handle, name);
    }

    template <>
    inline auto resources::bind(const std::string_view name, const resource_handle<texture> handle) -> void
    {
        textures.set_label(handle, name);
    }

    template <>
    inline auto resources::bind(const std::string_view name, const resource_handle<material> handle) -> void
    {
        materials.set_label(handle, name);
    }

    template <>
    inline auto resources::get_handle(const std::string_view name) const -> resource_handle<mesh>
    {
        return meshes.get_handle(name);
    }

    template <>
    inline auto resources::get_handle(const std::string_view name) const -> resource_handle<script>
    {
        return scripts.get_handle(name);
    }

    template <>
    inline auto resources::get_handle(const std::string_view name) const -> resource_handle<shader>
    {
        return shaders.get_handle(name);
    }

    template <>
    inline auto resources::get_handle(const std::string_view name) const -> resource_handle<texture>
    {
        return textures.get_handle(name);
    }

    template <>
    inline auto resources::get_handle(const std::string_view name) const -> resource_handle<material>
    {
        return materials.get_handle(name);
    }

    template <>
    inline auto resources::get_label(const resource_handle<mesh> handle) const -> std::string_view
    {
        return meshes.get_label(handle);
    }

    template <>
    inline auto resources::get_label(const resource_handle<script> handle) const -> std::string_view
    {
        return scripts.get_label(handle);
    }

    template <>
    inline auto resources::get_label(const resource_handle<shader> handle) const -> std::string_view
    {
        return shaders.get_label(handle);
    }

    template <>
    inline auto resources::get_label(const resource_handle<texture> handle) const -> std::string_view
    {
        return textures.get_label(handle);
    }

    template <>
    inline auto resources::get_label(const resource_handle<material> handle) const -> std::string_view
    {
        return materials.get_label(handle);
    }
} // namespace noi_engine
