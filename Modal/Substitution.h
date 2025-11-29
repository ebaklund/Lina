#pragma once

#include <cstdint>
#include <array>
#include <vector>

#include "Proposition.h"

namespace Modal
{
    template<typename T, uint32_t N>
    class Susbst
    {
        std::vector<Proposition<T, N>> _slots;
    };
}
