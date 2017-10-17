#pragma once

#include <glm/vec2.hpp>


namespace rharel::efficient_reformation::demo
{
    /// Describes the state of a vehicle embedded in a plane.
    struct Vehicle
    {
        /// Current position.
        glm::vec2 position;
        /// Target position.
        glm::vec2 target;

        /// Velocity magnitude.
        float speed;
    };
}
