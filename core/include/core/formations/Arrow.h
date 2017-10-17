#pragma once

#include <glm/vec2.hpp>

#include "Formation.h"


namespace rharel::efficient_reformation::core
{
    /// An arrow formation.
    ///
    /// An arrow is a triangular formation with a fixed number of rows. Each 
    /// row has more members than the previous one, with the first row having 
    /// exactly one member.
    class Arrow 
        : public Formation
    {
        public:
        /// Creates a new formation with the specified number of rows. Members 
        /// are equally spaced from one another by the specified amount.
        ///
        /// If the specified row count is <= 0, it is assumed to be 1 instead.
        /// If the specified spacing is <= 0, it is assumed to be 1 instead.
        explicit Arrow(unsigned int row_count, const glm::vec2& spacing);

        /// Computes formation positions for the specified number of members.
        /// The positions are stored in the specified output buffer.
        void get_member_positions(unsigned int member_count,
                                  glm::vec2*   positions) const override;

        private:
        const unsigned int row_count;
        const glm::vec2    spacing;
    };
}
