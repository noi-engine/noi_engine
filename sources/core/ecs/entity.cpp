//
// Created by ricka on 8/9/26.
//

#include <noi_engine/core/ecs/entity.hpp>

auto noi_engine::pack(const entity e) -> uint64_t
{
    return (static_cast<uint64_t>(e.m_generation) << 32) | e.m_id;
}

auto noi_engine::unpack(const uint64_t v) -> entity
{
    return entity{
        .m_id = static_cast<uint32_t>(v & 0xFFFFFFFF),
        .m_generation = static_cast<uint32_t>(v >> 32)
    };
}
