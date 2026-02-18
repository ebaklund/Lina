#pragma once
#include <cstddef>
#include <cstdint>
#include <array>
#include <memory>
#include <format>
#include "buffer_ops.hpp"

namespace Lina
{
    template <typename T, uint32_t N>
    std::string to_string(std::string name, std::array<T,N> arr)
    {
        const T* p = arr.data();
        const T* p_end = p + N;
        std::string s;
        s += name;
        s += ": [\n\t";

        while (p < p_end)
        {
            s += std::format("{:5.2f}, ", *(p++));
        }

        s += "]\n";
        return s;
    }
    
    template<typename T, uint32_t Dim>
    void randomize(std::array<T, Dim>& a1)
    {
        return randomize<T,Dim>(a1.data());
    }

    template <typename T, uint32_t Dim>
    T dot(std::array<T, Dim> const& a1, std::array<T, Dim> const& a2)
    {
        return dot<T,Dim>(a1.data(), a2.data());
    }

    template <typename T, uint32_t Dim>
    T nml1_dist(std::array<T, Dim> const& a1, std::array<T, Dim> const& a2)
    {
        return nml1_dist<T,Dim>(a1.data(), a2.data());
    }

    template <typename T, uint32_t Dim>
    void operator*=(std::array<T, Dim>& a, T x)
    {
        const T* p_end = a.data() + Dim;
        for(T* p = a.data(); p < p_end; ++p)
        {
            *p *= x;
        }
    }
}
