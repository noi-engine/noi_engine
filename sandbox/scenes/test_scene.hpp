//
// Created by ricka on 2026-07-30.
//

#pragma once

#include <noi_engine/core/scene.hpp>
#include "../../sources/core/glad/glad.h"

class test_scene: public noi_engine::scene
{
public:
	test_scene(): scene("test_scene")
	{
	}

	auto render() -> void override
	{
		glClearColor(
			0.2f,
			0.3f,
			0.4f,
			1.0f
		);

		glClear(GL_COLOR_BUFFER_BIT);
	}
};