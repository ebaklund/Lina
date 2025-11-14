#pragma once
#include <cstddef>
#include <cstdint>
#include <array>
#include <memory>
#include <format>

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
            T* _p = _data->data();
            T const* _p_end = _p + R*C;
            T const* p1 = data.data();

            while (_p < _p_end)
            {
                *(_p++) = *(p1++);
            }
        }

        std::array<T, R*C> const& data() const
        {
            return *_data;
        }

        std::string to_string(std::string name) const
        {
            const T* p = _data->data();
            const T* p_end = p +  R * C;
            std::string s;
            s += name;
            s += ": [\n";

            while (p < p_end)
            {
                s += "  ";
                auto p_eol = p + C;

                while (p < p_eol)
                {
                    s += std::format("{:5.2f}, ", *(p++));
                }

                s += "\n";
            }

            s += "]\n";
            return s;
        }

        template <uint32_t TL, uint32_t BL, uint32_t LL, uint32_t RL, uint32_t H = BL - TL, uint32_t W = RL - LL>
        Mtx<T, H, W> part()
        {
            Mtx<T, H, W> res;
            T* p = (T*)res.data().data();
            const T* p_end = p + H * W;
            const T* _p = _data->data() + TL * C + LL;

            while (p < p_end)
            {
                const T* p_eol = p + W;

                while (p < p_eol)
                {
                    *(p++) = *(_p++);
                }

                _p += (C - W);
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
}
