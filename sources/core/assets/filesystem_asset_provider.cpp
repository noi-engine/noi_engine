//
// Created by ricka on 8/2/26.
//

#include <fstream>
#include <stdexcept>
#include <utility>

#include <noi_engine/core/assets/filesystem_asset_provider.hpp>

noi_engine::filesystem_asset_provider::filesystem_asset_provider(std::filesystem::path root) : m_root(std::move(root))
{
}

auto noi_engine::filesystem_asset_provider::read(std::string_view path) -> std::vector<std::byte>
{
    const auto file_path = m_root / path;

    std::ifstream file(file_path, std::ios::binary | std::ios::ate);
    if (!file)
    {
        throw std::runtime_error("Cannot open asset: " + file_path.string());
    }

    const auto size = file.tellg();
    std::vector<std::byte> buffer(size);

    file.seekg(0);
    file.read(reinterpret_cast<char*>(buffer.data()), size);

    return buffer;
}
