//
// Created by ricka on 8/2/26.
//

#include <vector>
#include "texture_loader.hpp"
#include <stb_image.h>

auto noi_engine::texture_loader::load(const std::span<const std::byte> data) -> std::unique_ptr<texture>
{
    int width;
    int height;
    int channels;

    stbi_set_flip_vertically_on_load(true);
    const auto pixels = stbi_load_from_memory(
        reinterpret_cast<const unsigned char*>(data.data()),
        static_cast<int>(data.size()),
        &width,
        &height,
        &channels,
        4
    );

    std::vector<const std::byte> data(
        reinterpret_cast<std::byte*>(pixels),
        static_cast<std::span<const std::byte>::size_type>(width * height * 4)
    );

    return std::make_unique<texture>(
        width,
        height,
        std::move(data)
    );
}
