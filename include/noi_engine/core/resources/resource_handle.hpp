//
// Created by ricka on 8/1/26.
//

#pragma once

#include <cstdint>

namespace noi_engine
{
    template <typename T>
    struct resource_handle
    {
        uint32_t m_id{0};
        uint32_t m_generation{0};

        [[nodiscard]] auto operator==(const resource_handle& other) const -> bool = default;
    };
}
