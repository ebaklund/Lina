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

    template<typename T, uint32_t Dim>
    T nml1_dist(const T* p1, const T* p2)
    {
        // Normalized manhatten L1 distance (NML1D)
        // https://bib.dbvis.de/uploadedFiles/155.pdf
        // https://cs.brown.edu/~aritz/files/SDMpresentation.pdf

        T nmd_dist = T(0);

        for (int i = 0; i < Dim; ++i)
            nmd_dist += abs(p1[i] - p2[i]);

        nmd_dist /= Dim;
        return nmd_dist;
    }
}
