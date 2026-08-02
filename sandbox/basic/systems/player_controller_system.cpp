//
// Created by ricka on 8/2/26.
//

#include <SDL2/SDL_scancode.h>
#include <glm/geometric.hpp>

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

        if (input.is_key_down(SDL_SCANCODE_W) || input.is_key_down(SDL_SCANCODE_UP))
            direction.y += 1.0f;

        if (input.is_key_down(SDL_SCANCODE_S) || input.is_key_down(SDL_SCANCODE_DOWN))
            direction.y -= 1.0f;

        if (input.is_key_down(SDL_SCANCODE_D) || input.is_key_down(SDL_SCANCODE_RIGHT))
            direction.x += 1.0f;

        if (input.is_key_down(SDL_SCANCODE_A) || input.is_key_down(SDL_SCANCODE_LEFT))
            direction.x -= 1.0f;

        if (direction != glm::vec3{0.0f})
            direction = glm::normalize(direction);

        vel.value = direction * controller.speed;
    }
}
