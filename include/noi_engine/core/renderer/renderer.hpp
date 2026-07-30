//
// Created by ricka on 2026-07-30.
//

#pragma once

namespace noi_engine
{
	class renderer
	{
	public:
		renderer();

		virtual ~renderer() = default;

		auto begin_frame() -> void;

		auto end_frame() -> void;

		auto draw_test() -> void;
	};
}