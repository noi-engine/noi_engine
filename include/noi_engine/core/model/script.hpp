//
// Created by ricka on 8/9/26.
//

#pragma once

#include <utility>
#include <functional>
#include <memory>
#include <string>
#include <string_view>
#include <unordered_map>
#include <noi_engine/core/ecs/world.hpp>
#include <noi_engine/core/ecs/entity.hpp>
#include <noi_engine/core/input/input_state.hpp>

#define NOI_ENGINE_EMIT(Signal) \
	this->emit(self, context, Signal)

#define NOI_ENGINE_CONNECT(SignalType, TargetEntity, Lambda) \
	connect<SignalType>(context, TargetEntity, Lambda)

#define NOI_ENGINE_GET(Type) \
    this->get<Type>(self, context)

#define NOI_ENGINE_ADD(Value) \
    this->add(self, context, Value)

#define NOI_ENGINE_ADD_DIRTY_TRANSFORM() \
    this->add_dirty_transform(self, context)

#define NOI_ENGINE_ADD_TRANSFORM(Value) \
    this->add_transform(self, context)

#define NOI_ENGINE_ADD_DIRTY(Value) \
    this->add(self, context, dirty<Value>{})

#define NOI_ENGINE_HAS(Type) \
    this->has<Type>(self, context)

#define NOI_ENGINE_FIND_ENTITY(Name) \
    context.get_world().find_by_name(Name)

#define NOI_ENGINE_SCRIPT(Type) \
    private: \
    static inline const noi_engine::details::script_registrar<Type> s_script_registrar{ #Type }

namespace noi_engine
{
	//TODO: bad api
	class game;
	class scene;
	class renderer;
	class input_state;
	class resources;
	class script;

	namespace details
	{
		class script_registry
		{
			std::unordered_map<std::string, std::function<std::unique_ptr<script>()>> m_factories{};

		public:
			// Defined out-of-line in scripts.cpp (compiled only into libnoi_engine).
			// Keeping this inline here would let each shared object that includes this
			// header (e.g. a project's own scripts library, dlopen'd independently)
			// inline its own copy of the function-local static, producing a separate,
			// disconnected registry instead of the single process-wide one.
			static auto instance() -> script_registry&;

			auto add(const std::string_view name, std::function<std::unique_ptr<script>()> factory) -> void
			{
				m_factories[std::string(name)] = std::move(factory);
			}

			// Forgets every registered script (the editor does it before loading a rebuilt
			// scripts library, so deleted scripts disappear).
			auto clear() -> void
			{
				m_factories.clear();
			}

			[[nodiscard]] auto contains(const std::string_view name) const -> bool
			{
				return m_factories.contains(std::string(name));
			}

			[[nodiscard]] auto factories() const
				-> const std::unordered_map<std::string, std::function<std::unique_ptr<script>()>>&
			{
				return m_factories;
			}
		};

		template<typename T>
		struct script_registrar
		{
			explicit script_registrar(const std::string_view name)
			{
				script_registry::instance().add(name, []() -> std::unique_ptr<script>
				{
					return std::make_unique<T>();
				});
			}
		};
	} // namespace details

	struct script_context
	{
		game* game{ nullptr };
		scene* scene{ nullptr };
		input_state* input{ nullptr };
		renderer* renderer{ nullptr };
		resources* resources{ nullptr };

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

		auto add_dirty_transform(entity self, const script_context& ctx) -> void;

		auto add_transform(entity self, const script_context& ctx, const transform& value) -> void;

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