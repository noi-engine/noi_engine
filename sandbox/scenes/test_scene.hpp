//
// Created by ricka on 2026-07-30.
//

#pragma once

#include <noi_engine/core/scene.hpp>

class test_scene : public noi_engine::scene
{
public:
	test_scene() : scene("test_scene")
	{
	}

	auto render(noi_engine::renderer& renderer) -> void override
	{
	}
};