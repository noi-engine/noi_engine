//
// Created by ricka on 8/9/26.
//

#include "script_system.hpp"

#include <noi_engine/core/components/script_component.hpp>
#include <noi_engine/core/scripts/script.hpp>

namespace
{
	auto ensure_created(const noi_engine::script_context& context) -> void
	{
		auto& world = context.get_world();
		for (const auto e : world.view<noi_engine::script_component>())
		{
			auto& comp = world.get<noi_engine::script_component>(e);

			if (!comp.instance || comp.created)
			{
				continue;
			}

			comp.instance->on_create(e, context);
			comp.created = true;
		}
	}
}  // namespace

auto noi_engine::script_system::before_update(const script_context& context,
											  const float dt) -> void
{
	ensure_created(context);

	for (const auto e : context.get_world().view<script_component>())
	{
		if (const auto& comp = context.get_world().get<script_component>(e);
			comp.instance)
		{
			comp.instance->on_before_update(e, context, dt);
		}
	}
}

auto noi_engine::script_system::update(const script_context& context,
									   const float dt) -> void
{
	auto& world = context.get_world();
	for (const auto e : world.view<script_component>())
	{
		if (const auto& comp = world.get<script_component>(e); comp.instance)
		{
			comp.instance->on_update(e, context, dt);
		}
	}
}

auto noi_engine::script_system::after_update(const script_context& context,
											 const float dt) -> void
{
	auto& world = context.get_world();
	for (const auto e : world.view<script_component>())
	{
		if (const auto& comp = world.get<script_component>(e); comp.instance)
		{
			comp.instance->on_after_update(e, context, dt);
		}
	}
}

auto noi_engine::script_system::before_render(const script_context& context)
	-> void
{
	auto& world = context.get_world();
	for (const auto e : world.view<script_component>())
	{
		if (const auto& comp = world.get<script_component>(e); comp.instance)
		{
			comp.instance->on_before_render(e, context);
		}
	}
}

auto noi_engine::script_system::after_render(const script_context& context)
	-> void
{
	auto& world = context.get_world();
	for (const auto e : world.view<script_component>())
	{
		if (const auto& comp = world.get<script_component>(e); comp.instance)
		{
			comp.instance->on_after_render(e, context);
		}
	}
}

auto noi_engine::script_system::destroy(const script_context& context,
										const entity target) -> void
{
	auto& world = context.get_world();
	if (!world.has<script_component>(target))
	{
		return;
	}

	const auto& comp = world.get<script_component>(target);
	if (comp.instance && comp.created)
	{
		comp.instance->on_destroy(target, context);
	}
}
