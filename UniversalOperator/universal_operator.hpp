#pragma once
#include <cstddef>
#include <cstdint>
#include <algorithm>

namespace Lina
{
    template<typename T, uint32_t R1, uint32_t D, uint32_t C2>
    class UniversalOperator
    {
    private:
        // Fluent result values: 4 cells
        // Universal operators:  D per cell in R1*C2 result matrix 
        // Total fluents cout: 4 * D * R1 * C2
        static const uint32_t _size = 4 * D * R1 * C2;
        std::array<T, _size> _fluents;

    public:
        UniversalOperator()
        {
            std::fill(_fluents.begin(), _fluents.end(), T(.5f));
        }

        UniversalOperator(std::array<T, _size> const& f)
        {
            std::copy(f.begin(), f.end(), _fluents.begin());
        }

        // Note that the operation does not do transpose on the second argument for optimization.
        // That is expected to be done already on the input parameter "bt"
        void apply(const std::array<T,R1*D>& a, const std::array<T, D*C2>& bt, std::array<T, R1*C2>& c)
        {
            static const uint32_t CSIZE = R1 * C2;

            for (uint32_t ci = 0; ci < CSIZE; ++ci)
            {
                const T* ap = a.data() + D * ci / C2;
                const T* bp = bt.data() + D * ci % C2;
                const T* fp = _fluents.data() + ci * 4 * D;

                T cv = T(0);

                for (uint32_t dd = 0; dd < D; ++dd, fp += 4)
                {
                    const T  a = ap[dd];
                    const T na = T(1) - a;
                    const T  b = bp[dd];
                    const T nb = T(1) - b;

                    cv +=  a *  b * fp[0];
                    cv +=  a * nb * fp[1];
                    cv += na *  b * fp[2];
                    cv += na * nb * fp[3];
                }

                c.data()[ci] = cv / T(D);
            }
        }
    };
}
