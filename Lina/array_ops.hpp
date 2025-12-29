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

    template <typename T, uint32_t N>
    T dot(std::array<T, N> const& a1, std::array<T, N> const& a2)
    {
        return dot<T,N>(a1.data(), a2.data());
    }

    template <typename T, uint32_t N>
    T sin(std::array<T, N> const& a1, std::array<T, N> const& a2)
    {
        return sin<T,N>(a1.data(), a2.data());
    }
}
