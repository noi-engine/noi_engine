//
// Created by ricka on 2026-07-30.
//

#pragma once

#include <cstdint>

namespace noi_engine
{
    struct entity
    {
        uint32_t m_id;
        uint32_t m_generation;

        auto operator==(const entity&) const -> bool = default;
    };

    [[nodiscard]] auto pack(entity e) -> uint64_t;
    [[nodiscard]] auto unpack(uint64_t v) -> entity;
}
