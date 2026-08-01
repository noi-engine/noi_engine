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

		static auto begin_frame() -> void;

		static auto end_frame() -> void;

		auto draw_test() -> void;
	};
}