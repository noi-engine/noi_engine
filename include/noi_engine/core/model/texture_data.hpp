//
// Created by ricka on 8/1/26.
//

#pragma once

#include <cstdint>
#include <string>

namespace noi_engine
{
    class texture_data
    {
        uint32_t m_id{ 0 };
        int m_width{ 0 };
        int m_height{ 0 };

    public:
        explicit texture_data(const std::string& path);

        ~texture_data();

        texture_data(const texture_data&) = delete;

        auto operator=(const texture_data&) -> texture_data& = delete;

        texture_data(texture_data&& other) noexcept;

        auto operator=(texture_data&& other) noexcept -> texture_data&;

        [[nodiscard]] auto id() const noexcept -> uint32_t;

        [[nodiscard]] auto width() const noexcept -> int;

        [[nodiscard]] auto height() const noexcept -> int;
    };
}