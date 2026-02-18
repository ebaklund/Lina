#pragma once

namespace Lina
{
    template<typename T>
    T ubfun(T x, T y, T nx, T ny, const float* v)
    {
        T res = x*y*v[0] + x*ny*v[1] + nx*y*v[2] + nx*ny*v[3];
        return res;
    }

    template<typename T>
    T ubfun(T x, T y, const float* v)
    {
        static T n = T(1);
        return ubfun(x, y, n - x, n - y, v);
    }

    template<typename T>
    T learn_ubfun(T exp, T res, T x, T y, T nx, T ny, float* v)
    {
        static T learn = 0.9f;

        T diff = exp - res;

        if (diff >= 0.f)
        {
            v[0] += (1.f - v[0]) * learn * x*y;
            v[1] += (1.f - v[1]) * learn * x*ny;
            v[2] += (1.f - v[2]) * learn * nx*y;
            v[3] += (1.f - v[3]) * learn * nx*ny;
        } else
        {
            v[0] -= v[0] * learn * x*y;
            v[1] -= v[1] * learn * x*ny;
            v[2] -= v[2] * learn * nx*y;
            v[3] -= v[3] * learn * nx*ny;
        }

        return res;
    }

    template<typename T>
    T learn_ubfun(T exp, T res, T x, T y, float* v)
    {
        return learn_ubfun(exp, res, x, y, 1.f - x, 1.f - y, v);
    }
}