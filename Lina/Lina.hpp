#pragma once
#include <cstddef>
#include <cstdint>
#include <array>
#include <memory>
#include <format>
#include "Mtx.hpp"

namespace Lina
{
    template <typename T, uint32_t R, uint32_t C>
    bool operator==(Mtx<T, R, C> const& m1, Mtx<T, R, C> const& m2)
    {
        const T* p1 = m1.data().data();
        const T* p2 = m2.data().data();
        const T* p1_end = p1 + R * C;

        while (p1 < p1_end)
        {
            if (*(p1++) != *(p2++))
            {
                return false;
            }
        }

        return true;
    }

    template <typename T, uint32_t R, uint32_t C>
    Mtx<T, R, C> operator+(Mtx<T, R, C> const& m1, Mtx<T, R, C> const& m2)
    {
        Mtx<T, R, C> m;
        T* p= (T*)m.data().data();
        const T* p_end = p + R * C;

        const T* p1 = m1.data().data();
        const T* p2 = m2.data().data();

        while (p < p_end)
        {
            *(p++) = *(p1++) + *(p2++);
        }

        return m;
    }

    template <typename T, uint32_t R, uint32_t C>
    Mtx<T, R, C> operator-(Mtx<T, R, C> const& m1, Mtx<T, R, C> const& m2)
    {
        Mtx<T, R, C> m;
        T* p = (T*)m.data().data();
        const T* p_end = p + R * C;

        const T* p1 = m1.data().data();
        const T* p2 = m2.data().data();

        while (p < p_end)
        {
            *(p++) = *(p1++) - *(p2++);
        }

        return m;
    }

    template <typename U, uint32_t S>
    U dot(std::array<U, S> const& a1, std::array<U, S> const& a2)
    {
        U d = U(0);
        U const* p1 = a1.data();
        U const* p1_end = p1 + S;
        U const* p2 = a2.data();

        while (p1 < p1_end)
        {
            d += (*p1++) * (*p2++);
        }

        return d;
    }

    template <typename T, uint32_t C>
    T dot(Mtx<T, 1, C> const& m1, Mtx<T, 1, C> const& m2)
    {
        return dot(m1.data(), m2.data());
    }

    template <typename T, uint32_t R>
    T dot(Mtx<T, R, 1> const& m1, Mtx<T, R, 1> const& m2)
    {
        return dot(m1.data(), m2.data());
    }

    template <typename T, uint32_t R, uint32_t C>
    Mtx<T, C, R> t(const Mtx<T, R, C>& m1)
    {
        Mtx<T, C, R> t;
        T* p = (T*)t.data().data();
        T* p_end = p + R * C;
        const T* p1_begin = m1.data().data();

        while (p < p_end)
        {
            const T* p1 = p1_begin++;
            const T* p_eol = p + R;

            while (p < p_eol)
            {
                *(p++) = *p1;
                p1 += C;
            }
        }

        return t;
    }

    template <typename T, uint32_t R, uint32_t C>
    Mtx<T, R, C> operator*(T f, Mtx<T, R, C> const& m2)
    {
        Mtx<T, R, C> m;
        T* p = (T*)m.data().data();
        const T* p_end = p + R * C;
        const T* p2 = m2.data().data();

        while (p < p_end)
        {
            *(p++) = f * *(p2++);
        }

        return m;
    }

    template <typename T, uint32_t R1, uint32_t D, uint32_t C2>
    Mtx<T, R1, C2> operator*(Mtx<T, R1, D> const& m1, Mtx<T, D, C2> const& m2)
    {
        Mtx<T, R1, C2> m;
        const T* p_begin = (T*)m.data().data();
        const T* p_end = p_begin + R1 * C2;

        const T* p1_bod = m1.data().data();
        const T* p1_eod = p1_bod + D;

        Mtx<T, C2, D> mt = t(m2);
        const T* pt_begin = mt.data().data();
        const T* pt_end = pt_begin + C2 * D;

        for (T* p = (T*)p_begin; p < p_end;)
        {            
            for (const T* pt = pt_begin; pt < pt_end;)
            {
                T v = T(0);
                
                for (const T* p1 = p1_bod; p1 < p1_eod;)
                {
                    v += *(p1++) * *(pt++);
                }

                *(p++) = v;
            }

            p1_bod += D;
            p1_eod += D;
        }

        return m;
    }

    template <typename T, uint32_t R, uint32_t C1, uint32_t C2, uint32_t C = C1 + C2>
    Mtx<T, R, C> hcon(Mtx<T, R, C1> const& m1, Mtx<T, R, C2> const& m2)
    {
        Mtx<T, R, C> m;
        T* p = (T*)m.data().data();
        const T* p_end = p + R * C;
        const T* p1 = m1.data().data();
        const T* p2 = m2.data().data();

        while (p < p_end)
        {            
            for (const T* p_eol = p + C1; p < p_eol;)
            {
                *(p++) = *(p1++);
            }
           
            for (const T* p_eol = p + C2; p < p_eol;)
            {
                *(p++) = *(p2++);
            }
        }

        return m;
    }

    template <typename T, uint32_t R1, uint32_t R2, uint32_t C, uint32_t R = R1 + R2>
    Mtx<T, R, C> vcon(Mtx<T, R1, C> const& m1, Mtx<T, R2, C> const& m2)
    {
        Mtx<T, R, C> m;
        T* p = (T*)m.data().data();
        const T* p1 = m1.data().data();
        const T* p2 = m2.data().data();
        
        for (const T* p_end = p + R1 * C; p < p_end;)
        {
            *(p++) = *(p1++);
        }

        for (const T* p_end = p + R2 * C; p < p_end;)
        {
            *(p++) = *(p2++);
        }

        return m;
    }

    template <typename T, uint32_t R, uint32_t C>
    Mtx<T, R, 1> hsum(Mtx<T, R, C> const& m1)
    {
        Mtx<T, R, 1> m;
        T* p = (T*)m.data().data();
        const T* p_end = p + R;
        const T* p1 = m1.data().data();
        const T* p1_eol = p1;

        while (p < p_end)
        {
            *p = T(0);

            for (const T* p1_eol = p1 + C; p1 < p1_eol;)
            {
                *p += *(p1++);
            }

            p++;
        }

        return m;
    }

    template <typename T, uint32_t R, uint32_t C>
    Mtx<T, 1, C> vsum(Mtx<T, R, C> const& m1)
    {
        Mtx<T, 1, C> m;
        T* p = (T*)m.data().data();
        const T* p_end = p + R;
        const T* p1_bol = m1.data().data();
        const T* p1_end = p1_bol + R*C;

        while (p < p_end)
        {
            *p = T(0);

            for (const T* p1 = (p1_bol++); p1 < p1_end; p1 += C)
            {
                *p += *p1;
            }

            p++;
        }

        return m;
    }

    template <typename T, uint32_t R, uint32_t C>
    Mtx<T, R, C> rref(Mtx<T, R, C> const& m1)
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

        Mtx<T, R, C> m(m1.data());
        const T* dp = m.data().data();
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

        return m;
    }
}
