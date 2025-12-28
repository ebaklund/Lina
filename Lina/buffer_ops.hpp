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
}