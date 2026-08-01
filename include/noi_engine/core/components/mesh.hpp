//
// Created by ricka on 2026-07-30.
//

#pragma once

#include <noi_engine/core/model/mesh_data.hpp>
#include <noi_engine/core/resources/resource_handle.hpp>

namespace noi_engine
{
	struct mesh
	{
		resource_handle<mesh_data> m_handle{};
	};
}