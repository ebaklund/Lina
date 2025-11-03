

using System.Numerics;

namespace Lina;

public static class Mtx
{
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

    public Mtx(T[] data)
    {
        var expectedLength = _r.Count * _c.Count;

        if (data.Length != (expectedLength))
        {
            throw new ArgumentException($"Expected input array of length {expectedLength} but it is length {data.Length}.");
        }

        _data = data;
    }
}
