//
// Created by ricka on 8/17/26.
//

#pragma once

#include <memory>
#include <filesystem>
#include <string_view>
#include <noi_engine/core/scene.hpp>
#include <noi_engine/core/model/mesh.hpp>
#include <noi_engine/core/model/shader.hpp>
#include <noi_engine/core/model/texture.hpp>

namespace noi_engine
{
    class resource_system;

    class resource_loader
    {
    public:
        explicit resource_loader() = default;
        virtual ~resource_loader() = default;

        [[nodiscard]] virtual auto load(std::string_view path) -> std::vector<std::byte> = 0;
        [[nodiscard]] virtual auto load_obj(std::string_view path, resource_system* resources) -> std::unique_ptr<mesh> = 0;
        [[nodiscard]] virtual auto load_scene(std::string_view path, resource_system* resources) -> std::unique_ptr<scene> = 0;
        [[nodiscard]] virtual auto load_mesh_2d(std::string_view path, resource_system* resources) -> std::unique_ptr<mesh> = 0;
        [[nodiscard]] virtual auto load_shader(std::string_view path, resource_system* resources) -> std::unique_ptr<shader> = 0;
        [[nodiscard]] virtual auto load_texture(std::string_view path, resource_system* resources) -> std::unique_ptr<texture> = 0;
    };

    class source_resource_loader final : public resource_loader
    {
        std::filesystem::path m_root;
    public:
        explicit source_resource_loader(std::filesystem::path root = std::filesystem::current_path());

        [[nodiscard]] auto load(std::string_view path) -> std::vector<std::byte> override;
        [[nodiscard]] auto load_obj(std::string_view path) -> std::unique_ptr<mesh> override;
        [[nodiscard]] auto load_scene(std::string_view path) -> std::unique_ptr<scene> override;
        [[nodiscard]] auto load_mesh_2d(std::string_view path) -> std::unique_ptr<mesh> override;
        [[nodiscard]] auto load_shader(std::string_view path) -> std::unique_ptr<shader> override;
        [[nodiscard]] auto load_texture(std::string_view path) -> std::unique_ptr<texture> override;
    };

    class packaged_resource_loader final : public resource_loader
    {
    public:
        using resource_loader::resource_loader;

        [[nodiscard]] auto load_obj(std::string_view path) -> std::unique_ptr<mesh> override;
        [[nodiscard]] auto load_scene(std::string_view path) -> std::unique_ptr<scene> override;
        [[nodiscard]] auto load_mesh_2d(std::string_view path) -> std::unique_ptr<mesh> override;
        [[nodiscard]] auto load_shader(std::string_view path) -> std::unique_ptr<shader> override;
        [[nodiscard]] auto load_texture(std::string_view path) -> std::unique_ptr<texture> override;
    };
}
