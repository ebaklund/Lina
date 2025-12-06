#pragma once
#include <cstdint>
#include <format>

namespace Lina
{
    class Rational
    {
    private:
        int64_t _n = 0; // numerator
        int64_t _d = 1; // denominator

        bool eq(int64_t n1, int64_t d1, int64_t n2, int64_t d2) const
        {
            if (d1 == d2)
            {
                return n1 == n2;
            }

            int64_t v1 = n1 * d2; 
            int64_t v2 = n2 * d1; 
            return v1 == v2;
        }

    public:
        Rational()
        { }

        Rational(int64_t n, int64_t d = 1)
        {
            _n = n;
            _d = d;
        }

        // This function allows: auto r = Rational::from;
        static Rational from(int64_t n, int64_t d = 1)
        {
            return Rational(n, d);
        }

        std::wstring to_wstring() const
        {
            return std::format(L"({}/{})", _n, _d);
        }

        bool operator==(Rational r2) const
        {
            return eq(_n, _d, r2._n, r2._d);
            //if (_d == r2._d)
            //{
            //    return _n == r2._n;
            //}

            //int64_t n1 = _n * r2._d; 
            //int64_t n2 = r2._n * _d; 
            //return n1 == n2;
        }

        bool operator!=(Rational r2) const
        {
            return !eq(_n, _d, r2._n, r2._d);
        }
    };

}
