//
// Created by ricka on 8/2/26.
//

#include "texture_loader.hpp"
#include <stb_image.h>

auto noi_engine::texture_loader::load(const std::span<const std::byte> data) -> texture
{
    int width;
    int height;
    int channels;

    const auto pixels = stbi_load_from_memory(
        reinterpret_cast<const unsigned char*>(data.data()),
        static_cast<int>(data.size()),
        &width,
        &height,
        &channels,
        4
    );

    return texture(
        width,
        height,
        {
            reinterpret_cast<std::byte*>(pixels),
            static_cast<std::span<const std::byte>::size_type>(width * height * 4)
        }
    );
}
