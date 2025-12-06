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

        int64_t gcd(int64_t a, int64_t b)
        {
            while (b != 0)
            {
                int64_t t = b;
                b = a % b;
                a = t;
            }

            return a;
        }

        Rational& reduce()
        {
            if (_d != 1)
            {
                int64_t x = gcd(_n, _d);
                _n /= x;
                _d /= x;
            }

            return *this;
        }

        Rational add(int64_t n1, int64_t d1, int64_t n2, int64_t d2) const
        {
            if (d1 == d2)
            {
                auto n = n1 + n2;
                return Rational(n, d1).reduce();
            } else
            {
                auto n = n1 * d2 + n2 * d1;
                auto d = d1 * d2;
                return Rational(n, d).reduce();
            }
        }

        Rational mul(int64_t n1, int64_t d1, int64_t n2, int64_t d2) const
        {
            auto n = n1 * n2;
            auto d = d1 * d2;
            return Rational(n, d).reduce();
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
        }

        bool operator!=(Rational r2) const
        {
            return !eq(_n, _d, r2._n, r2._d);
        }

        Rational operator-() const
        {
            return Rational(-_n, _d);
        }

        Rational operator+(Rational r2) const
        {
            return add(_n, _d, r2._n, r2._d);
        }

        Rational operator-(Rational r2) const
        {
            return add(_n, _d, -r2._n, r2._d);
        }

        Rational& operator-=(Rational r2)
        {
            *this = add(_n, _d, -r2._n, r2._d);
            return *this;
        }

        Rational operator*(Rational r2) const
        {
            return mul(_n, _d, r2._n, r2._d);
        }

        Rational& operator*=(Rational r2)
        {
            *this = mul(_n, _d, r2._n, r2._d);
            return *this;
        }

        Rational operator/(Rational r2) const
        {
            return mul(_n, _d, r2._d, r2._n);
        }
    };
}
