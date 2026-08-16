//
// Created by ricka on 8/1/26.
//

#pragma once

#include <any>
#include <memory>
#include <noi_engine/core/assets/asset_provider.hpp>
#include <noi_engine/core/model/material.hpp>
#include <noi_engine/core/model/mesh.hpp>
#include <noi_engine/core/model/shader.hpp>
#include <noi_engine/core/model/texture.hpp>
#include <noi_engine/core/resources/details/resource_manager.hpp>
#include <noi_engine/core/scripts/script.hpp>

namespace noi_engine
{
	class resource_system
	{
		std::shared_ptr<asset_provider> m_asset_provider{};
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

		explicit resource_system(std::shared_ptr<asset_provider> assets);

		resource_system(const resource_system&) = delete;
		auto operator=(const resource_system&) -> resource_system& = delete;

		template<typename T>
		auto bind(const std::string_view name, resource_handle<T> handle)
			-> void
		{
			m_registry[std::string(name)] = handle;
		}

		template<typename T>
			requires std::derived_from<T, script>
		void register_script(const std::string_view name)
		{
			this->m_script_factories[std::string(name)] = []()
			{ return std::make_unique<T>(); };
		}

		auto load_shader(std::string_view path) -> resource_handle<shader>;
		auto load_shader(std::string_view name, std::string_view path)
			-> resource_handle<shader>;

		auto load_script(std::string_view name) -> resource_handle<script>;

		template<typename T>
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

		[[nodiscard]] auto add_script(std::unique_ptr<script> value)
			-> resource_handle<script>;

		auto add_script(std::string_view name, std::unique_ptr<script> value)
			-> resource_handle<script>;

		template<typename T>
		[[nodiscard]] auto add(std::unique_ptr<T> resource)
			-> resource_handle<T>;

		template<typename T>
		auto add(const std::string_view name, std::unique_ptr<T> resource)
			-> resource_handle<T>
		{
			const auto handle = this->add<T>(std::move(resource));
			this->bind<T>(name, handle);
			return handle;
		}

		[[nodiscard]] auto load_scene(std::string_view path)
			-> std::unique_ptr<scene>;

		auto load_mesh(std::string_view name, std::string_view path)
			-> resource_handle<mesh>;

		auto load_texture(std::string_view name, std::string_view path)
			-> resource_handle<texture>;

		[[nodiscard]] auto load_mesh(std::string_view path)
			-> resource_handle<mesh>;

		[[nodiscard]] auto load_texture(std::string_view path)
			-> resource_handle<texture>;
	};

	template<>
	inline auto resource_system::add(std::unique_ptr<shader> resource)
		-> resource_handle<shader>
	{
		return shaders.create(std::move(resource));
	}

	template<>
	inline auto resource_system::add(std::unique_ptr<mesh> resource)
		-> resource_handle<mesh>
	{
		return meshes.create(std::move(resource));
	}

	template<>
	inline auto resource_system::add(std::unique_ptr<script> resource)
		-> resource_handle<script>
	{
		return scripts.create(std::move(resource));
	}

	template<>
	inline auto resource_system::add(std::unique_ptr<texture> resource)
		-> resource_handle<texture>
	{
		return textures.create(std::move(resource));
	}

	template<>
	inline auto resource_system::add(std::unique_ptr<material> resource)
		-> resource_handle<material>
	{
		return materials.create(std::move(resource));
	}
}  // namespace noi_engine
