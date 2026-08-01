//
// Created by ricka on 8/1/26.
//

#pragma once

#include <noi_engine/core/resources/resource_handle.hpp>
#include <noi_engine/core/model/material.hpp>
#include <noi_engine/core/model/mesh.hpp>

namespace noi_engine
{
    struct mesh_renderer
    {
        resource_handle<mesh> m_mesh{};
        resource_handle<material> m_material{};
    };
}
