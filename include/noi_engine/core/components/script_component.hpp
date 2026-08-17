//
// Created by ricka on 8/9/26.
//

#pragma once

#include <vector>
#include <noi_engine/core/model/script.hpp>
#include <noi_engine/core/components/component.hpp>
#include <noi_engine/core/resources/resource_handle.hpp>

namespace noi_engine
{
	struct script_component : component
	{
		std::vector<resource_handle<script>> scripts{};
		bool created{ false };
	};
}  // namespace noi_engine
