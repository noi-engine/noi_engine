//
// Created by ricka on 8/9/26.
//

#pragma once

#include <utility>
#include <functional>
#include <noi_engine/core/ecs/world.hpp>
#include <noi_engine/core/ecs/entity.hpp>
#include <noi_engine/core/input/input_state.hpp>

namespace noi_engine
{
	//TODO: bad api
	class game;
	class scene;
	class renderer;
	class input_state;
	class resource_system;

	struct script_context
	{
		game* game{ nullptr };
		scene* scene{ nullptr };
		input_state* input{ nullptr };
		renderer* renderer{ nullptr };
		resource_system* resources{ nullptr };

		[[nodiscard]] auto get_world() const -> world&;
	};

	class script
	{
	public:
		script() = default;
		script(const script&) = default;
		script(script&&) noexcept = default;
		auto operator=(const script&) -> script& = default;
		auto operator=(script&&) noexcept -> script& = default;

		virtual ~script() = default;

		virtual auto on_create(entity self, const script_context& ctx) -> void;
		virtual auto on_before_update(entity self, const script_context& ctx,
									  float dt) -> void;
		virtual auto on_update(entity self, const script_context& ctx, float dt)
			-> void;
		virtual auto on_after_update(entity self, const script_context& ctx,
									 float dt) -> void;
		virtual auto on_before_render(entity self, const script_context& ctx)
			-> void;
		virtual auto on_after_render(entity self, const script_context& ctx)
			-> void;
		virtual auto on_destroy(entity self, const script_context& ctx) -> void;

	protected:
		template<typename T>
		[[nodiscard]] auto get(const entity self,
							   const script_context& ctx) const
			-> decltype(auto)
		{
			return ctx.get_world().get<T>(self);
		}

		template<typename T>
		auto add(const entity self, const script_context& ctx, T value) const
			-> void
		{
			ctx.get_world().add<T>(self, std::move(value));
		}

		template<typename T>
		[[nodiscard]] auto has(const entity self,
							   const script_context& ctx) const -> bool
		{
			return ctx.get_world().has<T>(self);
		}

		template<typename Signal>
			requires details::is_signal<Signal>
		auto emit(const entity self, const script_context& ctx, Signal signal)
			-> void
		{
			signal.source = self;
			ctx.get_world().signals().emit<Signal>(std::move(signal));
		}

		template<typename Signal>
			requires details::is_signal<Signal>
		auto connect(const script_context& ctx, const entity source,
					 std::function<void(float dt, const Signal&)> callback)
		{
			return ctx.get_world().signals().connect<Signal>(
				source, std::move(callback));
		}

		template<typename Signal>
			requires details::is_signal<Signal>
		auto connect(const script_context& ctx,
					 std::function<void(float dt, const Signal&)> callback)
		{
			return ctx.get_world().signals().connect<Signal>(
				std::move(callback));
		}

	};
}  // namespace noi_engine