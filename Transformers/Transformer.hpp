#pragma once
#include <cstdint>  
#include <array>  
#include <Lina/buffer_ops.hpp>  

namespace Lina
{
    template<typename T, uint32_t N_in, uint32_t N_out> 
    class Transformer
    {
    private:
    public:
        template<typename T, uint32_t Dim>
        std::array<T,Dim> get_next(std::array<T,Dim> input)
        {
            std::array<T,N_out> output;
            randomize<T,Dim>(output);

            return output;
        }

        void learn_from(T score)
        {
        }
    };
}