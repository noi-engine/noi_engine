//
// Created by ricka on 8/1/26.
//

#pragma once

#include <cstdint>
#include <string>

namespace noi_engine
{
    class texture
    {
        uint32_t m_id{ 0 };
        int m_width{ 0 };
        int m_height{ 0 };

    public:
        explicit texture(const std::string& path);

        ~texture();

        texture(const texture&) = delete;

        auto operator=(const texture&) -> texture& = delete;

        texture(texture&& other) noexcept;

        auto operator=(texture&& other) noexcept -> texture&;

        auto bind(uint32_t slot) const -> void;

        [[nodiscard]] auto id() const noexcept -> uint32_t;

        [[nodiscard]] auto width() const noexcept -> int;

        [[nodiscard]] auto height() const noexcept -> int;
    };
}