#pragma once
#include <cstddef>
#include <cstdint>
#include <array>


// Gauss-Jordan elimination (gje)
// An algorithm for transforming a matrix into its reduced row echelon form.

namespace Lina
{
    template <typename T, uint32_t R, uint32_t C>
    uint32_t  apply_gje(std::array<T, R*C>& data)
    {
        auto col_has_nze_in_row_or_below = [](const T* dp, uint32_t r, uint32_t c, uint32_t& row_of_nze) -> bool
        {
            const T* p_end = dp + R * C;
            const T* p = dp + r * C + c;

            for (; (p < p_end) && (*p == T(0)); p += C);

            bool nze_found = p < p_end;

            if (nze_found)
            {
                row_of_nze = (p - dp) / C;
            }

            return nze_found;
        };
        auto swap_rows = [](const T* dp, uint32_t r1, uint32_t r2) -> void
        {
            T* p1 = (T*)dp + r1 * C;
            T* p2 = (T*)dp + r2 * C;
            const T* p1_eor = p1 + C;

            while (p1 < p1_eor)
            {
                T tmp = *p1;
                *(p1++) = *p2;
                *(p2++) = tmp;
            }
        };
        auto pivot_row = [](const T* dp, uint32_t r, uint32_t c) -> void 
        {
            const T* p_bor = dp + r * C;
            const T* p_eor = p_bor + C;

            T* p = (T*)p_bor + c;
            const T inv = T(1)/(*p);

            *(p++) = T(1);

            while (p < p_eor)
            {
                *(p++) *= inv;
            }
        };
        auto reduce_row_below = [](const T* dp, uint32_t r, uint32_t c, uint32_t row_below) -> void
        {
            T* pb = (T*)dp + row_below * C + c;
            T vb = *pb;

            // Step 7
            if (vb == T(0))
            {
                return;
            }

            const T* p = dp + r * C + c;
            const T* pb_end = dp + row_below * C + C;

            *(pb++) = T(0);

            while (pb < pb_end)
            {
                *(pb++) -= vb * *(p++);
            }
        };

        const T* dp = data.data();
        const T* dp_end = dp + R * C;
        const T* cp_end = dp + C;
        uint32_t rank = 0;

        // Step 1 and 8
        for (uint32_t r = 0; r < R; r++)
        {
            uint32_t row_of_nze;
            uint32_t c = 0;

            // Step 2
            for (; (c < C) && !col_has_nze_in_row_or_below(dp, r, c, row_of_nze); c++);

            if (c == C)
            {
                break; // Done. All zeros in or below row.
            }

            rank++;

            // Step 3
            if (r != row_of_nze)
            {
                swap_rows(dp, r, row_of_nze);
            }

            // Step 4
            T nze_value = *(dp + r * C + c);

            if (nze_value != T(1))
            {
                pivot_row(dp, r, c);
            }

            // Step 5 and 7
            for (uint32_t row_below = r + 1; row_below < R; row_below++)
            {
                // Step 6
                reduce_row_below(dp, r, c, row_below);
            }
        }

        return rank;
    }
}
