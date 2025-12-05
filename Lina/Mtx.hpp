#pragma once
#include <cstddef>
#include <cstdint>
#include <array>
#include <memory>
#include <format>

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

        Mtx(std::unique_ptr<std::array<T, R*C>>& data )
        {
            _data = data;
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

        std::array<T, R*C> const& data() const
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
            const T* p_bol = (T*)_data->data();
            const T* p_end = p_bol + R * C;
            int last_seen_none_zero_col = -1;

            for (; p_bol < p_end; p_bol += C)
            {                
                const T* p = p_bol;
                const T* p_eol = p_bol + C;

                for(; (p < p_eol) && (*p == T(0)); p++);
                
                bool found_zero_row = p == p_eol;
                
                if (found_zero_row)
                {
                    last_seen_none_zero_col = C;
                    continue;
                }
                
                // R2: Leftmost nonzero element must be 1
                bool r2_failed = *p != T(1);

                if (r2_failed)
                {
                    return false;
                }

                // R1: All nonzero rows must precede zero rows
                // R3: All elements below in column of leftmost nonzero element must be zero
                // R4: All none zero elements above must appear to the right of current leftmost nonzero element.
                int current_col = p + C - p_eol; // Current none zero column
                bool r134_failed = current_col <= last_seen_none_zero_col;

                if (r134_failed)
                {
                    return false;
                }

                last_seen_none_zero_col = current_col; 
            }

            bool is_resh = true; 
            return is_resh;
        }
    };
}

namespace xxx
{
    class koko
    {
    };
}
