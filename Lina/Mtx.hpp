#pragma once
#include <cstddef>
#include <cstdint>
#include <array>
#include <memory>
#include <format>
#include "gje.hpp"
#include "array_ops.hpp"

namespace Lina
{
    template <typename T, uint32_t R, uint32_t C>
    class Mtx
    {
    private:
        std::unique_ptr<std::array<T, R*C>> _data;

    public:
        Mtx()
        {
            _data = std::make_unique<std::array<T, R* C>>();
        }

        Mtx(std::unique_ptr<std::array<T, R*C>>& data)
        {
            _data = std::move(data);
        }

        Mtx(const std::array<T, R*C>& data) 
        {            
            _data = std::make_unique<std::array<T, R* C>>();
            T* _p = _data->data();
            T const* _p_end = _p + R*C;
            T const* p1 = data.data();

            while (_p < _p_end)
            {
                *(_p++) = *(p1++);
            }
        }

        void randomize()
        {
            Lina::randomize(*_data);
        }

        std::array<T, R*C> const& data() const
        {
            return *_data;
        }

        std::array<T, R*C> & mdata() const
        {
            return *_data;
        }

        std::string to_string(std::string name) const
        {
            const T* p = _data->data();
            const T* p_end = p +  R * C;
            std::string s;
            s += name;
            s += ": [\n";

            while (p < p_end)
            {
                s += "  ";
                auto p_eol = p + C;

                while (p < p_eol)
                {
                    s += std::format("{:5.2f}, ", *(p++));
                }

                s += "\n";
            }

            s += "]\n";
            return s;
        }

        template <uint32_t TL, uint32_t BL, uint32_t LL, uint32_t RL, uint32_t H = BL - TL, uint32_t W = RL - LL>
        Mtx<T, H, W> part()
        {
            Mtx<T, H, W> res;
            T* p = (T*)res.data().data();
            const T* p_end = p + H * W;
            const T* _p = _data->data() + TL * C + LL;

            while (p < p_end)
            {
                const T* p_eol = p + W;

                while (p < p_eol)
                {
                    *(p++) = *(_p++);
                }

                _p += (C - W);
            }

            return res;
        }

        bool is_rref()
        {
            return Lina::is_rref<T, R, C>(*_data);
        }

        void operator*=(T x)
        {
            (*_data) *= x;
        }
    };
}
