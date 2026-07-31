//
// Created by ricka on 2026-07-30.
//

#pragma once

#include <glm/vec3.hpp>

namespace noi_engine
{
	struct transform
	{
		glm::vec3 position{ 0.0f };
		glm::vec3 rotation{ 0.0f };
		glm::vec3 scale{ 1.0f };
	};
}