#pragma once
#include <cstddef>
#include <cstdint>
#include <array>
#include <memory>

namespace Lina
{
    template <typename T, std::uint32_t R, std::uint32_t C>
    class Mtx
    {
    private:
        std::array<T, R*C> _data;

    public:
        Mtx()
        {
        }

        Mtx(std::array<T, R*C> data)
        {
            _data = data;
        }

        std::array<T, R*C>& data()
        {
            return _data;
        }

        bool operator==(const Mtx<T, R, C>& m2) const {
            const T* p1 = this->_data.data();
            const T* p2 = m2._data.data();
            const T* p1_end = p1 + R*C;

            while (p1 < p1_end)
            {
                if (*(p1++) != *(p2++))
                {
                    return false;
                }
            }

            return true;
        }

        std::unique_ptr<Mtx<T, R, C>> operator+(const Mtx<T, R, C>& m2) const {
            auto m3 = std::make_unique<Mtx<T, R, C>>();
            const T* p1 = this->_data.data();
            const T* p2 = m2._data.data();
            T* p3 = m3->_data.data();
            const T* p1_end = p1 + R * C;

            while (p1 < p1_end)
            {
                *(p3++) = *(p1++) + *(p2++);
            }

            return m3;
        }
    };

    template <typename U, std::uint32_t S>
    U dot(std::array<U, S>& a1, std::array<U, S>& a2)
    {
        U d = U(0);
        U* p1_end = a1.data() + S;
        U* p1 = a1.data();
        U* p2 = a2.data();

        while (p1 < p1_end)
        {
            d += (*p1++) * (*p2++);
        }

        return d;
    }

    template <typename T, std::uint32_t C>
    T dot(Mtx<T, 1, C>& m1, Mtx<T, 1, C>& m2)
    {
        return dot(m1.data(), m2.data());
    }

    template <typename T, std::uint32_t R>
    T dot(Mtx<T, R, 1>& m1, Mtx<T, R, 1>& m2)
    {
        return dot(m1.data(), m2.data());
    }

    template <typename T, std::uint32_t R, std::uint32_t C>
    std::unique_ptr<Mtx<T, C, R>> t(Mtx<T, R, C>& m1)
    {
        auto mt = std::make_unique<Mtx<T, C, R>>();
        T* p1 = m1.data().data();
        T* pt0 = mt->data().data();

        for (std::uint32_t r = 0; r < R; r++)
        {
            T* pt = pt0 + r * C;
            for (T* p1_end = p1 + C; p1 < p1_end; p1++)
            {
                *pt = *p1;
                pt += R;
            }
        }

        return mt;
    }
}
