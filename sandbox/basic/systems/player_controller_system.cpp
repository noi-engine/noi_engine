//
// Created by ricka on 8/2/26.
//

#include <glm/geometric.hpp>
#include <noi_engine/core/input/input_codes.hpp>

#include "player_controller_system.hpp"
#include "../components/player_controller.hpp"
#include "../components/velocity.hpp"

auto sandbox::basic::player_controller_system::update(noi_engine::world& world,
                                                      const noi_engine::input_state& input) -> void
{
    for (const auto e : world.view<player_controller, velocity>())
    {
        const auto& controller = world.get<player_controller>(e);
        auto& vel = world.get<velocity>(e);

        auto direction = glm::vec3{0.0f};

        if (input.is_key_down(noi_engine::key_code::up))
            direction.y += 1.0f;

        if (input.is_key_down(noi_engine::key_code::down))
            direction.y -= 1.0f;

        if (input.is_key_down(noi_engine::key_code::right))
            direction.x += 1.0f;

        if (input.is_key_down(noi_engine::key_code::left))
            direction.x -= 1.0f;

        if (direction != glm::vec3{0.0f})
            direction = glm::normalize(direction);

        vel.value = direction * controller.speed;
    }
}
