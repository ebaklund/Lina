#pragma once
#include <cstddef>
#include <cstdint>
#include <array>
#include <memory>
#include <format>
#include "Mtx.hpp"
#include "gje.hpp"

namespace Lina
{
    template <typename T, uint32_t R, uint32_t C>
    class RrefMtx : public Mtx<T, R, C>
    {
    private:
        uint32_t _rank;

        RrefMtx(std::unique_ptr<std::array<T, R*C>>& data, const uint32_t rank) : Mtx<T, R, C>(data)
        {
            _rank = rank;
        }

    public:
        RrefMtx()
        { }

        static RrefMtx<T, R, C> from(const Mtx<T, R, C>& m1)
        {
            auto data = std::make_unique<std::array<T, R*C>>(m1.data());
            uint32_t rank = apply_gje<T,R,C>(*data);
            auto m = RrefMtx<T, R, C>(data, rank);

            return m;
        }

        uint32_t rank()
        {
            return _rank;
        }

        bool operator==(const Mtx<T, R, C>& m1)
        {
            return this->data() == m1.data();
        }
    };

    template <typename T, uint32_t R, uint32_t C>
    RrefMtx<T, R, C> rref(const Mtx<T, R, C>& m1)
    {
        return RrefMtx<T, R, C>::from(m1);
    }
}
