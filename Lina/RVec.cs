
using System;

namespace Lina;

public class RVec<D>(D _dim) : Vec<D>(_dim) where D : Dim
{
    // PUBLIC

    public RVec<D> Copy(float[] data)
    {
        Array.Copy(data, _data, _dim.N);
        return this;
    }

    public RVec<D> Clone()
    {
        return new RVec<D>(_dim).Copy(base._data);
    }

    public CVec<D> Trf()
    {
        return new CVec<D>(_dim).Copy(base._data);
    }
}
