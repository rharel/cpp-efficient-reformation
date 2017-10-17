#pragma once

#include <glm/vec2.hpp>


namespace rharel::efficient_reformation::core
{
    /// A formation of vehicles.
    class Formation
    {
        public:
        /// Computes formation positions for the specified number of members
        /// and stores them in the specified buffer.
        virtual void get_member_positions(unsigned int member_count, 
                                          glm::vec2*   positions) const = 0;
    };
}
