//
// Created by ricka on 8/17/26.
//

#include <noi_engine/core/resources/resource_loader.hpp>
#include <fstream>
#include <stdexcept>
#include <utility>
#include ""

namespace noi_engine
{
    source_resource_loader::source_resource_loader(std::filesystem::path root) : m_root(std::move(root))
    {
    }

    auto source_resource_loader::load(std::string_view path) -> std::vector<std::byte>
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

    auto source_resource_loader::load_mesh_2d(const std::string_view path) -> std::unique_ptr<mesh>
    {
    }
}
