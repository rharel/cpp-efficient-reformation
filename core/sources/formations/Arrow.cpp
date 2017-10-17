#include <algorithm>

#include <glm/common.hpp>

#include "core/formations/Arrow.h"


using namespace rharel::efficient_reformation::core;


Arrow::Arrow(const unsigned int row_count, 
             const glm::vec2&   spacing)
    : row_count(std::max(row_count, 1u)),
      spacing(glm::max(spacing, glm::vec2(1, 1)))
{}
void Arrow::get_member_positions(const unsigned int member_count,
                                 glm::vec2*         positions) const
{
    using glm::vec2;

    // Let s(i) be the size of row i [where s(0) = 1 is the tip of the arrow, 
    // and size of further rows increasing with each increment of i].
    // 
    // Let r be the row count.
    // 
    // It is the case that the size of row i is:
    //   s(0) = 1               for i = 0
    //   s(i) = id + 1          for 0 < i < r
    // 
    // Where d is the constant difference in row size from one row to the next.
    //
    // Taking the sum N of s(i) from 0 <= i < r we get:
    //   N = 1 + (d + 1) + (2d + 1) ... + ((r - 1)d + 1)
    //     = r + d * (1 + 2 + ... + (r-1))
    //     = r + d * (r * (r - 1)) / 2
    // 
    // N is known - it is the member count of the formation. So solve for d:
    //   d = (N - r) / ((r * (r - 1)) / 2)
    //
    const unsigned int N = member_count,
                       r = row_count;
    const unsigned int d = (N - r) / ((r * (r - 1)) / 2) + 1;

    const float height = r * spacing.y,   // Formation height;
                y0     = -0.5f * height;  // Base row offset.

    unsigned int k = 0;  // Index of current position to compute.

    for (unsigned int i = 0; i < r; ++i)
    {
        const unsigned int s = std::min(i * d + 1, N - k);
        
        const float width = s * spacing.x,  // Row width.
                    x0    = -0.5f * width;  // Leftmost member offset.

        for (unsigned int j = 0; j < s; ++j, ++k)
        {
            positions[k].x = x0 + j * width  / s;
            positions[k].y = y0 + i * height / r;
        }
    }
}
