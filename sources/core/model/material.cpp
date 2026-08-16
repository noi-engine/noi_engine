//
// Created by ricka on 8/1/26.
//

#include <noi_engine/core/model/material.hpp>
#include <noi_engine/core/model/shader.hpp>
#include <noi_engine/core/model/texture.hpp>
#include <noi_engine/core/resources/resource_system.hpp>
#include <utility>

namespace noi_engine
{
	auto material::set_shader(const resource_handle<noi_engine::shader> shader)
		-> void
	{
		m_shader = shader;
	}

	auto material::set_color(std::string name, const glm::vec4 color) -> void
	{
		m_colors[std::move(name)] = color;
	}

	auto material::set_parameter(std::string name, const float value) -> void
	{
		m_parameters[std::move(name)] = value;
	}

	auto material::set_texture(std::string name,
							   const resource_handle<texture> texture) -> void
	{
		m_textures[std::move(name)] = texture;
	}

	auto material::shader() const noexcept
		-> resource_handle<noi_engine::shader>
	{
		return m_shader;
	}

	auto material::apply(const noi_engine::shader& shader,
						 resource_system& resources) -> void
	{
		for (const auto& [name, value] : m_parameters)
		{
			shader.set_float(name, value);
		}

		for (const auto& [name, color] : m_colors)
		{
			shader.set_vec4(name, color);
		}

		int slot = 0;
		for (const auto& [name, texture_handle] : m_textures)
		{
			const auto texture = resources.textures.get(texture_handle);
			texture->bind(slot);

			shader.set_int(name, slot);
			++slot;
		}
	}
}  // namespace noi_engine
