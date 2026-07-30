//
// Created by ricka on 2026-07-30.
//

#include <noi_engine/core/renderer/renderer.hpp>
#include "glad/glad.h"

noi_engine::renderer::renderer()
{
}

auto noi_engine::renderer::begin_frame() -> void
{
	glClearColor(
		0.1f,
		0.1f,
		0.1f,
		1.0f
		);

	glClear(GL_COLOR_BUFFER_BIT);
}

auto noi_engine::renderer::end_frame() -> void
{
}

auto noi_engine::renderer::draw_test() -> void
{
}