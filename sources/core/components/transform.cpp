//
// Created by ricka on 8/1/26.
//

#include <noi_engine/core/components/transform.hpp>
#include <glm/ext/matrix_transform.hpp>

auto noi_engine::transform::model() const -> glm::mat4
{
    auto result = glm::mat4{1.0f};

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
