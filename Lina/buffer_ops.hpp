#pragma once
#include <cstdint>

namespace Lina
{
    template<typename T, uint32_t N>
    T dot(const T* p1, const T* p2)
    {
        auto dot = T(0);

        for(uint32_t i = 0; i < N; ++i)
        {
            dot += p1[i] * p2[i];
        }

        return dot;
    }

    template<typename T, uint32_t N>
    T length(const T* p1)
    {
        auto sqr_sum = T(0);

        for(uint32_t i = 0; i < N; ++i)
        {
            sqr_sum += p1[i] * p1[i];
        }

        T length = sqrt(sqr_sum);
        return length;
    }

    template<typename T, uint32_t N>
    void normalize(T* p1, const T* p2)
    {
        T length2 = length<T,N>(p2);

        for(uint32_t i = 0; i < N; ++i)
        {
            p1[i] = p2[i] / length2;
        }
    }

    template<typename T, uint32_t N>
    T sin(const T* p1, const T* p2)
    {
        std::array<T,N> n1;
        std::array<T,N> n2;

        normalize<T,N>(n1.data(), p1);
        normalize<T,N>(n2.data(), p2);

        T sin = T(1) - dot<T,N>(n1.data(), n2.data());
        return sin;
    }
}