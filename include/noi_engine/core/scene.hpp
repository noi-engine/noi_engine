//
// Created by ricka on 2026-07-30.
//

#pragma once
#include <string>

namespace noi_engine
{
	class scene
	{
		std::string m_name{};

	public:
		explicit scene(const std::string& name);

		virtual auto render() -> void;

		virtual auto update(float dt) -> void;

		virtual ~scene() = default;
	};
}