
using Shouldly;

namespace Lina.Tests.Schaums;

record D1() : Dim(1);
record D2() : Dim(2);
record D3() : Dim(3);

public class MO_1
{
    [Fact]
    public void Debug()
    {
    }

    [Fact]
    public void Problem_1_1()
    {
        var zero = new Mtx<float, D1, D1>( [0] );
        var one = new Mtx<float, D1, D1>( [1] );
        var b = new Mtx<float, D1, D1>( [0.5f] );

        var A = new Mtx<float, D3, D1>( [2,  3,  4] );
        var B = new Mtx<float, D3, D1>( [5,  6, -7] );
        var C = new Mtx<float, D1, D3>( [7, -8, -9] );

        Mtx.Dot(zero, zero).ShouldBe(0);
        Mtx.Dot(zero, one).ShouldBe(0);
        Mtx.Dot(one, zero).ShouldBe(0);
        Mtx.Dot(one, one).ShouldBe(1);

        Mtx.Dot(b, b).ShouldBe(0.25f);
        Mtx.Dot(b, one).ShouldBe(0.5f);
        Mtx.Dot(one, b).ShouldBe(0.5f);
        Mtx.Dot(one, one).ShouldBe(1.0f);

        Mtx.Dot(A, B).ShouldBe(0.0f);
        Mtx.Dot(B, Mtx.T(C)).ShouldBe(50.0f);

        A.Dot(B).ShouldBe(0.0f);
        B.Dot(C.T()).ShouldBe(50.0f);
    }

    [Fact]
    public void Problem_1_2()
    {
        var A = new Mtx<float, D2, D2>([
            0, 1,
            2, 3
        ]); 

        var B = new Mtx<float, D2, D2>([
            4,  5,
            6, -7
        ]);

        var C = new Mtx<float, D2, D2>([
            4,  6,
            8, -4
        ]);

        Mtx.Eq(Mtx.Add(A, B), C).ShouldBeTrue();
        A.Add(B).Eq(C).ShouldBeTrue();
        ((A + B) == C).ShouldBeTrue();
        ((B + A) == C).ShouldBeTrue();
    }
}
