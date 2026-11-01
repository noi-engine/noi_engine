//
// Created by ricka on 2026-07-30.
//

#pragma once

#include <algorithm>
#include <memory>
#include <string>
#include <type_traits>
#include <typeindex>
#include <utility>
#include <vector>

#include <noi_engine/core/ecs/entity.hpp>
#include <noi_engine/core/ecs/world.hpp>
#include <noi_engine/core/input/input_state.hpp>
#include <noi_engine/core/renderer/renderer.hpp>
#include <noi_engine/core/system.hpp>

namespace noi_engine
{
	class game;

	struct scene_context
	{
		game* game{ nullptr };
		renderer* renderer{ nullptr };
		input_state* input{ nullptr };
		resources* resources{ nullptr };
	};

	class scene
	{
	protected:
		world m_world{};
		std::string m_name{};
		entity m_camera_entity{};

	private:
		struct system_slot
		{
			std::type_index type;
			std::unique_ptr<system> instance;
			int priority;
		};

		std::vector<system_slot> m_systems{};
		bool m_scripts_paused{ false };

		[[nodiscard]] auto find_system_slot(std::type_index type)
			-> std::vector<system_slot>::iterator;

		auto resort_systems() -> void;

	public:
		explicit scene(std::string name);

		virtual auto render(const scene_context& context) -> void;

		virtual auto on_enter(const scene_context& context) -> void;
		virtual auto on_exit(const scene_context& context) -> void;

		virtual auto update(const scene_context& context, float dt) -> void;

		virtual auto on_resize(const scene_context& context, int width,
							   int height) -> void;

		[[nodiscard]] auto get_aspect_ratio() -> float;

		[[nodiscard]] auto get_world() -> world&;

		[[nodiscard]] auto get_camera_entity() const -> entity;

		// Paused scripts don't run at all (no on_create, no updates): the editor pauses them
		// outside Play mode so the scene shows as authored.
		auto set_scripts_paused(bool paused) -> void;
		[[nodiscard]] auto scripts_paused() const -> bool;

		template <typename T, typename... Args>
		auto add_system(Args&&... args) -> T&
		{
			return add_system<T>(0, std::forward<Args>(args)...);
		}

		template <typename T, typename... Args>
		auto add_system(const int priority, Args&&... args) -> T&
		{
			static_assert(std::is_base_of_v<system, T>, "T must derive from noi_engine::system");

			m_systems.push_back(system_slot{ std::type_index(typeid(T)),
											 std::make_unique<T>(std::forward<Args>(args)...), priority });
			resort_systems();

			return *get_system<T>();
		}

		template <typename Anchor, typename T, typename... Args>
		auto add_system_before(Args&&... args) -> T&
		{
			static_assert(std::is_base_of_v<system, T>, "T must derive from noi_engine::system");

			const auto anchor = find_system_slot(std::type_index(typeid(Anchor)));
			const auto priority = anchor != m_systems.end() ? anchor->priority : 0;

			m_systems.insert(anchor, system_slot{ std::type_index(typeid(T)),
												  std::make_unique<T>(std::forward<Args>(args)...), priority });
			resort_systems();

			return *get_system<T>();
		}

		template <typename Anchor, typename T, typename... Args>
		auto add_system_after(Args&&... args) -> T&
		{
			static_assert(std::is_base_of_v<system, T>, "T must derive from noi_engine::system");

			const auto anchor = find_system_slot(std::type_index(typeid(Anchor)));
			const auto priority = anchor != m_systems.end() ? anchor->priority : 0;
			const auto insert_at = anchor != m_systems.end() ? anchor + 1 : m_systems.end();

			m_systems.insert(insert_at, system_slot{ std::type_index(typeid(T)),
													 std::make_unique<T>(std::forward<Args>(args)...), priority });
			resort_systems();

			return *get_system<T>();
		}

		template <typename T>
		auto remove_system() -> void
		{
			const auto it = find_system_slot(std::type_index(typeid(T)));
			if (it != m_systems.end())
				m_systems.erase(it);
		}

		template <typename T>
		[[nodiscard]] auto get_system() -> T*
		{
			const auto it = find_system_slot(std::type_index(typeid(T)));
			return it != m_systems.end() ? static_cast<T*>(it->instance.get()) : nullptr;
		}

		template <typename T>
		auto set_system_priority(const int priority) -> void
		{
			const auto it = find_system_slot(std::type_index(typeid(T)));
			if (it == m_systems.end())
				return;

			it->priority = priority;
			resort_systems();
		}

		[[nodiscard]] auto systems() const -> std::vector<std::pair<std::string_view, int>>;

		virtual ~scene() = default;
	};
}  // namespace noi_engine
