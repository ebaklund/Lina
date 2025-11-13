#pragma once
#include <cstddef>
#include <cstdint>
#include <array>
#include <memory>

namespace Lina
{
    template <typename T, uint32_t R, uint32_t C>
    class Mtx
    {
    private:
        std::unique_ptr<std::array<T, R*C>> _data = std::make_unique<std::array<T, R* C>>();

    public:
        Mtx()
        { }

        Mtx(std::array<T, R*C> const data) 
        {            
            T* p1 = _data->data();
            T const* p1_end = p1 + R*C;
            T const* p2 = data.data();

            while (p1 < p1_end)
            {
                *(p1++) = *(p2++);
            }
        }

        std::array<T, R*C> const& data() const
        {
            return *_data;
        }

        template <uint32_t TL, uint32_t BL, uint32_t LL, uint32_t RL, uint32_t H = BL - TL, uint32_t W = RL - LL>
        Mtx<T, H, W> part()
        {
            Mtx<T, H, W> res;
            T* p = (T*)res.data().data();
            const T* p_end = p + H * W;
            const T* p1 = _data->data() + TL * C + LL;

            while (p < p_end)
            {
                const T* p1_end = p1 + W;

                while (p1 < p1_end)
                {
                    *(p++) = *(p1++);
                }

                p1 += (C - W);
            }

            return res;
        }
    };

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
        Mtx<T, R, C> m3;
        const T* p1 = m1.data().data();
        const T* p2 = m2.data().data();
        T* p3 = (T*)m3.data().data();
        const T* p1_end = p1 + R * C;

        while (p1 < p1_end)
        {
            *(p3++) = *(p1++) + *(p2++);
        }

        return m3;
    }

    template <typename T, uint32_t R, uint32_t C>
    Mtx<T, R, C> operator-(Mtx<T, R, C> const& m1, Mtx<T, R, C> const& m2)
    {
        Mtx<T, R, C> m3;
        const T* p1 = m1.data().data();
        const T* p2 = m2.data().data();
        T* p3 = (T*)m3.data().data();
        const T* p1_end = p1 + R * C;

        while (p1 < p1_end)
        {
            *(p3++) = *(p1++) - *(p2++);
        }

        return m3;
    }

    template <typename U, uint32_t S>
    U dot(std::array<U, S> const& a1, std::array<U, S> const& a2)
    {
        U d = U(0);
        U const* p1_end = a1.data() + S;
        U const* p1 = a1.data();
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
        Mtx<T, C, R> mt;
        const T* p1 = m1.data().data();
        T* ptc = (T*)mt.data().data();
        T* ptc_end = ptc + R;

        while (ptc < ptc_end)
        {
            T* pt = ptc++;
            const T* p1c_end = p1 + C;
            
            while(p1 < p1c_end)
            {
                *pt = *(p1++);
                pt += R;
            }
        }

        return mt;
    }

    template <typename T, uint32_t R, uint32_t C>
    Mtx<T, R, C> operator*(T f, Mtx<T, R, C> const& m2)
    {
        Mtx<T, R, C> m3;
        const T* p2 = m2.data().data();
        T* p3 = (T*)m3.data().data();
        const T* p2_end = p2 + R * C;

        while (p2 < p2_end)
        {
            *(p3++) = f * *(p2++);
        }

        return m3;
    }

    template <typename T, uint32_t R1, uint32_t D, uint32_t C2>
    Mtx<T, R1, C2> operator*(Mtx<T, R1, D> const& m1, Mtx<T, D, C2> const& m2)
    {
        Mtx<T, C2, D> mt = t(m2);
        Mtx<T, R1, C2> m3;
        
        const T* p1_begin = m1.data().data();
        const T* pt_begin = mt.data().data();
        T* p3 = (T*)m3.data().data();

        for (uint32_t i3 = 0; i3 < (R1 * C2); i3++, p3++)
        {            
            *p3 = T(0);
            const T* p1 = p1_begin + D * (i3 / C2);
            const T* pt = pt_begin + D * (i3 % C2);
            const T* pt_d = pt + D;

            while (pt < pt_d)
            {
                *p3 += *(p1++) * *(pt++);
            }
        }

        return m3;
    }
}
