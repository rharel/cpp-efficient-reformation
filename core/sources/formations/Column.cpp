#include <algorithm>

#include <glm/common.hpp>

#include "core/formations/Column.h"


using namespace rharel::efficient_reformation::core;


Column::Column(const unsigned int row_size, 
               const glm::vec2&   spacing)
    : row_size(std::max(row_size, 1u)),
      spacing(glm::max(spacing, glm::vec2(1, 1)))
{}
void Column::get_member_positions(const unsigned int member_count,
                                  glm::vec2*         positions) const
{
    using glm::vec2;

    // Since the number of members may not be divisible by the formation's row 
    // size, the last row may be only partially full. Let us label such a 
    // scenario as an 'imperfect' formation.
    const unsigned int full_row_count     = member_count / row_size,
                       imperfect_row_size = member_count % row_size,
                       row_count          = full_row_count + 
                                           (imperfect_row_size > 0 ? 1 : 0);

    // Computes the formation's spatial dimensions:
    const float width  = (row_size  - 1) * spacing.x,
                height = (row_count - 1) * spacing.y;
    
    const vec2 offset(-0.5 * width, 
                      -0.5 * height);

    unsigned int k = 0;  // Index of current position to compute.
    // Compute positions for full rows:
    for (unsigned int i = 0; i < full_row_count; ++i)
    {
        for (unsigned int j = 0; j < row_size; ++j, ++k)
        {
            positions[k].x = offset.x + j * width  / row_size;
            positions[k].y = offset.y + i * height / row_count;
        }
    }
    if (imperfect_row_size > 0)
    {
        // Compute positions for the imperfect row:
        const auto  relative_width = static_cast<float>(imperfect_row_size) / 
                                     row_size;
        const float padding_x      = 0.5f * width * (1 - relative_width);
        for (unsigned int j = 0; j < imperfect_row_size; ++j, ++k)
        {
            positions[k].x = padding_x + offset.x + j * relative_width * 
                             width / imperfect_row_size;
            positions[k].y = offset.y  + height - spacing.y;
        }
    }
}
