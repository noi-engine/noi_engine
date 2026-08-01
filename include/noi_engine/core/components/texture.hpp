//
// Created by ricka on 8/1/26.
//

#pragma once

#include <noi_engine/core/model/texture_data.hpp>
#include <noi_engine/core/resources/resource_handle.hpp>

namespace noi_engine
{
    struct texture
    {
        resource_handle<texture_data> m_texture{};
    };
}
