
using System;

namespace Lina;

public class CVec<D>(D _dim) : Vec<D>(_dim) where D : Dim
{
    // PUBLIC

    public CVec<D> Copy(float[] data)
    {
        Array.Copy(data, _data, _dim.N);
        return this;
    }

    public CVec<D> Clone()
    {
        return new CVec<D>(_dim).Copy(base._data);
    }

    public RVec<D> Trf()
    {
        return new RVec<D>(_dim).Copy(base._data);
    }
}
