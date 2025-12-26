#pragma once
#include <cstddef>
#include <cstdint>
#include <array>
#include <memory>
#include <format>

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
}
