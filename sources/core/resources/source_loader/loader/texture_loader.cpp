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

    const auto size = static_cast<std::size_t>(width * height * 4);

    std::vector bytes(
        reinterpret_cast<const std::byte*>(pixels),
        reinterpret_cast<const std::byte*>(pixels) + size
    );

    return std::make_unique<texture>(
        width,
        height,
        std::move(bytes)
    );
}
