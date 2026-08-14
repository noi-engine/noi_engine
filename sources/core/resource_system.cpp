//
// Created by ricka on 8/2/26.
//

#include <noi_engine/core/resources/resource_system.hpp>

#include "assets/mesh_loader.hpp"
#include "assets/texture_loader.hpp"

noi_engine::resource_system::resource_system(std::shared_ptr<asset_provider> assets) : m_asset_provider(
    std::move(assets))
{
}

auto noi_engine::resource_system::add_texture(const std::string_view path) -> resource_handle<texture>
{
    auto data = this->m_asset_provider->read(path);
    auto mapped = texture_loader::load(data);

    return this->add<texture>(std::move(mapped));
}

auto noi_engine::resource_system::add_mesh(std::string_view path) -> resource_handle<mesh>
{
    auto data = this->m_asset_provider->read(path);
    auto mapped = mesh_loader::load(data);

    mapped.upload(); //TODO

    return this->add<mesh>(std::move(mapped));
}
