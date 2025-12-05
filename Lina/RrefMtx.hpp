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
    class RrefMtx : Mtx
    {
    private:
        uint32_t _rank;

        RrefMtx(const uint32_t rank, std::array<T, R*C>& data) : Mtx(data)
        {
            _rank = rank;
        }

    public:
        RrefMtx()
        { }

        static RrefMtx<T, R, C> From(const Mtx<T, R, C>& m)
        {
        }

        uint32_t rank()
        {
            return _rank;
        }
    };
}
