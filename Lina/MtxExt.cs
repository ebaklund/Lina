

using System.Numerics;

namespace Lina;
public static class MtxExt
{
    public static Mtx<T,C,R> T<T,R,C>(this Mtx<T,R,C> a)
        where T : INumber<T> 
        where R : Dim, new() 
        where C : Dim, new()
    {
        return Mtx.T(a);
    }

    public static T Dot<T,R,C>(this Mtx<T,R,C> a, Mtx<T,R,C> b)
        where T : INumber<T> 
        where R : Dim, new() 
        where C : Dim, new()
    {
        return Mtx.Dot(a, b);
    }

    public static bool Eq<T,R,C>(this Mtx<T,R,C> a, Mtx<T,R,C> b)
        where T : INumber<T> 
        where R : Dim, new() 
        where C : Dim, new()
    {
        return Mtx.Eq(a, b);
    }

    public static Mtx<T,R,C> Add<T,R,C>(this Mtx<T,R,C> a, Mtx<T,R,C> b)
        where T : INumber<T> 
        where R : Dim, new() 
        where C : Dim, new()
    {
        return Mtx.Add(a, b);
    }
}
