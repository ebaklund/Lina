#pragma once
#include <cstdint>  
#include <array>  

namespace Lina
{
    template<typename T, uint32_t N_in, uint32_t N_out> 
    class Transformer
    {
    private:
    public:
        std::array<T,N_out> get_next(std::array<T,N_in> input)
        {
            std::array<T,N_out> output;

            return output;
        }

        void learn_from(T score)
        {
        }
    };
}