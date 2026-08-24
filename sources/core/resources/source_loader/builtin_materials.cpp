//
// Created by ricka on 8/23/26.
//

#include "builtin_shaders.hpp"
#include "builtin_materials.hpp"
#include <noi_engine/core/model/shader.hpp>
#include <memory>

namespace noi_engine
{
    static auto load_color_material(const resources* resources) -> std::unique_ptr<material>
    {
        auto instance = std::make_unique<material>();
        instance->set_color("u_color", {1, 0, 0, 1});
        instance->set_shader(resources->get_handle<shader>(NOI_ENGINE_BUILTIN_COLOR_SHADER_NAME));

        return std::move(instance);
    }

    static auto load_texture_material(const resources* resources) -> std::unique_ptr<material>
    {
        auto instance = std::make_unique<material>();
        instance->set_shader(resources->get_handle<shader>(NOI_ENGINE_BUILTIN_TEXTURE_SHADER_NAME));

        return std::move(instance);
    }

    auto builtin_materials::load(const std::string_view name, resources* resources) -> std::unique_ptr<material>
    {
        static const std::unordered_map<std::string_view, std::function<std::unique_ptr<material>()>> loaders = {
            {
                NOI_ENGINE_BUILTIN_COLOR_MATERIAL_NAME, [resources]() -> std::unique_ptr<material>
                {
                    return load_color_material(resources);
                }
            },
            {
                NOI_ENGINE_BUILTIN_TEXTURE_MATERIAL_NAME, [resources]() -> std::unique_ptr<material>
                {
                    return load_texture_material(resources);
                }
            }
        };

        if (const auto it = loaders.find(name); it != loaders.end())
        {
            return it->second();
        }

        return nullptr;
    }
} // namespace noi_engine
