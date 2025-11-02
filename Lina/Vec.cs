
namespace Lina;

public class Vec<D>(D _dim) where D : Dim
{
    // PROTECTED

    protected float[] _data = new float[_dim.N];

    // PUBLIC

    public float Dot()
    {
        float dot = 0;

        for (uint i = 0; i < _dim.N; i++)
        {
            var x = _data[i];
            dot += (x * x);
        }

        return dot;
    }
}
