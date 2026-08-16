//
// Created by ricka on 8/2/26.
//

#include <noi_engine/core/resources/resource_system.hpp>

#include "assets/mesh_loader.hpp"
#include "assets/scene_loader.hpp"
#include "assets/texture_loader.hpp"

noi_engine::resource_system::resource_system(
	std::shared_ptr<asset_provider> assets)
	: m_asset_provider(std::move(assets))
{
}
auto noi_engine::resource_system::add_script(std::unique_ptr<script> value)
	-> resource_handle<script>
{
	return this->add<script>(std::move(value));
}

auto noi_engine::resource_system::add_script(const std::string_view name,
											 std::unique_ptr<script> value)
	-> resource_handle<script>
{
	return this->add(name, std::move(value));
}

auto noi_engine::resource_system::load_scene(const std::string_view path) const
	-> std::unique_ptr<scene>
{
	const auto data = this->m_asset_provider->read(std::string(path));
	return scene_loader::load(data);
}

auto noi_engine::resource_system::load_texture(const std::string_view name,
											   const std::string_view path)
	-> resource_handle<texture>
{
	const auto handle = this->load_texture(path);
	this->bind<texture>(name, handle);
	return handle;
}

auto noi_engine::resource_system::load_mesh(const std::string_view name,
											const std::string_view path)
	-> resource_handle<mesh>
{
	const auto handle = this->load_mesh(path);
	this->bind<mesh>(name, handle);
	return handle;
}

auto noi_engine::resource_system::load_texture(const std::string_view path)
	-> resource_handle<texture>
{
	auto data = this->m_asset_provider->read(path);
	auto mapped = texture_loader::load(data);

	return this->add<texture>(std::make_unique<texture>(std::move(mapped)));
}

auto noi_engine::resource_system::load_mesh(std::string_view path)
	-> resource_handle<mesh>
{
	auto data = this->m_asset_provider->read(path);
	auto mapped = mesh_loader::load(data);

	return this->add<mesh>(std::make_unique<mesh>(std::move(mapped)));
}
