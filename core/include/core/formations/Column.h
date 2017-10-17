#pragma once

#include <glm/vec2.hpp>

#include "Formation.h"


namespace rharel::efficient_reformation::core
{
    /// A column formation.
    ///
    /// A column is a rectangular formation with a fixed number of vehicles per
    /// row and a dynamic number of rows.
    class Column 
        : public Formation
    {
        public:
        /// Creates a new formation with the specified number of vehicles per
        /// row. Members are equally spaced from one another by the specified 
        /// amount.
        ///
        /// If the specified row size is <= 0, it is assumed to be 1 instead.
        /// If the specified spacing is <= 0, it is assumed to be 1 instead.
        explicit Column(unsigned int row_size, const glm::vec2& spacing);

        /// Computes formation positions for the specified number of members.
        /// The positions are stored in the specified output buffer.
        void get_member_positions(unsigned int member_count,
                                  glm::vec2*   positions) const override;

        private:
        const unsigned int row_size;
        const glm::vec2    spacing;
    };
}
