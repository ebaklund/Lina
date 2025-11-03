

using System.Numerics;

namespace Lina;

public static class Mtx
{
    // Dot()
    public static T Dot<T, R, C>(Mtx<T,R,C> a, Mtx<T,R,C> b)
        where T : INumber<T> 
        where R : Dim, new() 
        where C : Dim, new()
    {
        T res = T.Zero;

        for (uint i = 0; i < a._data.Length; i++) {
            res += (a._data[i] * b._data[i]);
        }

        return res;
    }

    // T()
    public static Mtx<T,C,R> T<T, R, C>(Mtx<T,R,C> a)
        where T : INumber<T> 
        where R : Dim, new() 
        where C : Dim, new()
    {
        // Mind the swap!
        uint tcCount = new R().Count;
        uint trCount = new C().Count;
        var tData = new T[a._data.Length];

        uint i = 0;
       for (uint tc = 0; tc < tcCount; tc++) {
            var tOffset = tc * trCount;

            for (uint tr = 0; tr < trCount; tr++) {
                tData[tr + tOffset] = a._data[i++];
            }
        }

        return new Mtx<T,C,R>(tData);
    }

    // Eq()
    public static bool Eq<T, R, C>(Mtx<T,R,C> a, Mtx<T,R,C> b)
        where T : INumber<T> 
        where R : Dim, new() 
        where C : Dim, new()
    {
        uint i = 0;
        for (;  (i < a._data.Length) && (a._data[i] == b._data[i]); i++);

        return i == a._data.Length;
    }

    // Ne()
    public static bool Ne<T, R, C>(Mtx<T,R,C> a, Mtx<T,R,C> b)
        where T : INumber<T> 
        where R : Dim, new() 
        where C : Dim, new()
    {
        return ! Eq(a, b);
    }

    // Add()
    public static Mtx<T,R,C> Add<T, R, C>(Mtx<T,R,C> a, Mtx<T,R,C> b)
        where T : INumber<T> 
        where R : Dim, new() 
        where C : Dim, new()
    {
        var data = new T[a._data.Length];

        for (uint i = 0; i < a._data.Length; i++) {
            data[i] = a._data[i] + b._data[i];
        }

        return new Mtx<T,R,C>(data);
    }
}


public class Mtx<T, R, C>
    where T : INumber<T> 
    where R : Dim, new() 
    where C : Dim, new()
{
    // PRIVATE

    private readonly R _r = new R();
    private readonly C _c = new C();
    internal readonly T[] _data;

    // PUBLIC

    public Mtx(T[] data)
    {
        var expectedLength = _r.Count * _c.Count;

        if (data.Length != (expectedLength))
        {
            throw new ArgumentException($"Expected input array of length {expectedLength} but it is length {data.Length}.");
        }

        _data = data;
    }

    public static bool operator ==(Mtx<T, R, C> a, Mtx<T, R, C> b)
    {
        return Mtx.Eq(a, b);
    }

    public static bool operator !=(Mtx<T, R, C> a, Mtx<T, R, C> b)
    {
        return Mtx.Ne(a, b);
    }

    public static Mtx<T, R, C> operator +(Mtx<T, R, C> a, Mtx<T, R, C> b)
    {
        return Mtx.Add(a, b);
    }
}
