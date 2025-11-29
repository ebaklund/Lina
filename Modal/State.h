#pragma once

#include <cstdint>
#include <array>
#include <vector>

#include "Proposition.h"

namespace Modal
{
    template <typename T, uint32_t N>
    class State
    {
    private:
        std::vector<Proposition<T, N>> _propositions;

    public:
        State()
        {
        }

        void add(const std::array<T, N>& p)
        {
            _propositions.push_back(p);
            return *this;
        }
    };
}