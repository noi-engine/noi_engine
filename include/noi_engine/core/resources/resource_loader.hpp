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
    class resources;

    class resource_loader
    {
    public:
        explicit resource_loader() = default;
        virtual ~resource_loader() = default;

        virtual auto load(std::string_view path) -> std::vector<std::byte> = 0;
        virtual auto load_obj(std::string_view path, resources* resources) -> std::unique_ptr<mesh> = 0;
        virtual auto load_scene(std::string_view path, resources* resources) -> std::unique_ptr<scene> = 0;
        virtual auto load_mesh_2d(std::string_view path, resources* resources) -> std::unique_ptr<mesh> = 0;
        virtual auto load_shader(std::string_view path, resources* resources) -> std::unique_ptr<shader> = 0;
        virtual auto load_texture(std::string_view path, resources* resources) -> std::unique_ptr<texture> = 0;
        virtual auto load_material(std::string_view path, resources* resources) -> std::unique_ptr<material> = 0;
    };

    class source_resource_loader final : public resource_loader
    {
        std::filesystem::path m_root;

    public:
        explicit source_resource_loader(std::filesystem::path root = std::filesystem::current_path());

        auto load(std::string_view path) -> std::vector<std::byte> override;
        auto load_obj(std::string_view path, resources* resources) -> std::unique_ptr<mesh> override;
        auto load_scene(std::string_view path, resources* resources) -> std::unique_ptr<scene> override;
        auto load_mesh_2d(std::string_view path, resources* resources) -> std::unique_ptr<mesh> override;
        auto load_shader(std::string_view path, resources* resources) -> std::unique_ptr<shader> override;
        auto load_texture(std::string_view path, resources* resources) -> std::unique_ptr<texture> override;
        auto load_material(std::string_view path, resources* resources) -> std::unique_ptr<material> override;

        source_resource_loader(const source_resource_loader&) = default;
        auto operator=(const source_resource_loader&) -> source_resource_loader& = default;
    };

    class compiled_resource_loader final : public resource_loader
    {
        std::filesystem::path m_root;
        source_resource_loader m_source_loader;

    public:
        explicit compiled_resource_loader(std::filesystem::path root = std::filesystem::current_path());

        auto load(std::string_view path) -> std::vector<std::byte> override;
        auto load_obj(std::string_view path, resources* resources) -> std::unique_ptr<mesh> override;
        auto load_scene(std::string_view path, resources* resources) -> std::unique_ptr<scene> override;
        auto load_mesh_2d(std::string_view path, resources* resources) -> std::unique_ptr<mesh> override;
        auto load_shader(std::string_view path, resources* resources) -> std::unique_ptr<shader> override;
        auto load_texture(std::string_view path, resources* resources) -> std::unique_ptr<texture> override;
        auto load_material(std::string_view path, resources* resources) -> std::unique_ptr<material> override;
    };
}
