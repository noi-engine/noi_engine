//
// Created by ricka on 8/9/26.
//

#include "script_system.hpp"

#include <noi_engine/core/model/script.hpp>
#include <noi_engine/core/resources/resources.hpp>
#include <noi_engine/core/components/script_component.hpp>

namespace
{
	template<typename Func>
	auto for_each_script(const noi_engine::script_context& context, Func&& fn)
		-> void
	{
		auto& world = context.get_world();
		for (const auto e : world.view<noi_engine::script_component>())
		{
			auto& comp = world.get<noi_engine::script_component>(e);
			for (const auto& handle : comp.scripts)
			{
				if (auto* script_ptr = context.resources->scripts.get(handle))
				{
					fn(e, *script_ptr);
				}
			}
		}
	}

	auto ensure_created(const noi_engine::script_context& context) -> void
	{
		auto& world = context.get_world();
		for (const auto e : world.view<noi_engine::script_component>())
		{
			auto& comp = world.get<noi_engine::script_component>(e);

			if (comp.created)
			{
				continue;
			}

			for (const auto& handle : comp.scripts)
			{
				if (auto* script_ptr = context.resources->scripts.get(handle))
				{
					script_ptr->on_create(e, context);
				}
			}

			comp.created = true;
		}
	}
}  // namespace

namespace noi_engine
{
	auto script_system::before_update(const script_context& context,
									  const float dt) -> void
	{
		ensure_created(context);
		for_each_script(context, [&](entity e, script& s)
						{ s.on_before_update(e, context, dt); });
	}

	auto script_system::update(const script_context& context, const float dt)
		-> void
	{
		for_each_script(
			context, [&](entity e, script& s) { s.on_update(e, context, dt); });
	}

	auto script_system::after_update(const script_context& context,
									 const float dt) -> void
	{
		for_each_script(context, [&](entity e, script& s)
						{ s.on_after_update(e, context, dt); });
	}

	auto script_system::before_render(const script_context& context) -> void
	{
		for_each_script(context, [&](entity e, script& s)
						{ s.on_before_render(e, context); });
	}

	auto script_system::after_render(const script_context& context) -> void
	{
		for_each_script(context, [&](entity e, script& s)
						{ s.on_after_render(e, context); });
	}

	auto script_system::destroy(const script_context& context,
								const entity target) -> void
	{
		auto& world = context.get_world();
		if (!world.has<script_component>(target))
		{
			return;
		}

		if (auto& comp = world.get<script_component>(target); comp.created)
		{
			for (const auto& handle : comp.scripts)
			{
				if (auto* script_ptr = context.resources->scripts.get(handle))
				{
					script_ptr->on_destroy(target, context);
				}
			}
			comp.created = false;
		}
	}
}  // namespace noi_engine
