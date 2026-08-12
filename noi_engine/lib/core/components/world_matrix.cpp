//
// Created by ricka on 8/2/26.
//

#include <noi_engine/core/components/world_matrix.hpp>
#include <glm/ext/matrix_transform.hpp>

auto noi_engine::world_matrix::from(const transform& transform) -> glm::mat4
{
    auto result = glm::mat4{1.0f};
    const auto position = transform.position;
    const auto rotation = transform.rotation;
    const auto scale = transform.scale;

    result = glm::translate(result, position);

    result = glm::rotate(
        result,
        glm::radians(rotation.x),
        glm::vec3{1.0f, 0.0f, 0.0f}
    );

    result = glm::rotate(
        result,
        glm::radians(rotation.y),
        glm::vec3{0.0f, 1.0f, 0.0f}
    );

    result = glm::rotate(
        result,
        glm::radians(rotation.z),
        glm::vec3{0.0f, 0.0f, 1.0f}
    );

    result = glm::scale(result, scale);
    return result;
}
