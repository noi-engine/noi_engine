//
// Created by ricka on 8/16/26.
//

#pragma once

#include <noi_engine/core/components/component.hpp>
#include <string>

namespace noi_engine
{
	struct name_component : component
	{
		std::string name;
	};
}  // namespace noi_engine