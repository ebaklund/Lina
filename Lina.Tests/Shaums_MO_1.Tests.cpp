
#include "CppUnitTest.h"
#include "..\Lina\Lina.hpp"

using namespace Lina;
using namespace Microsoft::VisualStudio::CppUnitTestFramework;


namespace LinaTests
{
	TEST_CLASS(LinaTests)
	{
	public:
        TEST_METHOD(MO_1_0)
        {
            Mtx<float, 2, 3> A({
                2.f, 3.f, 4.f,
                5.f, 6.f, 7.f
            });
            Mtx<float, 3, 2> tA({
                2.f, 5.f,
                3.f, 6.f,
                4.f, 7.f
            });

            Assert::AreEqual(t(A) == tA, true);
        }

		TEST_METHOD(MO_1_1)
		{
            Mtx<float, 3, 1> A ({ 2.f,  3.f,  4.f }); 
            Mtx<float, 3, 1> B ({ 5.f,  6.f, -7.f });
            Mtx<float, 1, 3> C ({ 7.f, -8.f, -9.f });
            
            Assert::AreEqual(dot(A, B), 0.f);
            Assert::AreEqual(dot(B, t(C)), 50.f);
        }

        TEST_METHOD(MO_1_2)
        {
            Mtx<float, 2, 2> A({
                0.f,  1.f,
                2.f,  3.f
            });
            Mtx<float, 2, 2> B({
                4.f,  5.f,
                6.f, -7.f
            });
            Mtx<float, 2, 2> C({
                4.f,  6.f,
                8.f, -4.f
            });

            Assert::AreEqual((A + B) == C, true);
            Assert::AreEqual((B + A) == C, true);
        }

        TEST_METHOD(MO_1_3)
        {
            Mtx<float, 2, 2> A({
                0.f,  1.f,
                2.f,  3.f
            });
            Mtx<float, 2, 2> B({
                4.f,  5.f,
                6.f, -7.f
            });
            Mtx<float, 2, 2> C({
               -2.0f,  0.5f,
                3.0f, 12.5f
            });

            Assert::AreEqual(3.0f * A - 0.5f * B == C, true);
        }

        TEST_METHOD(MO_1_4)
        {
            Mtx<float, 2, 2> A({
                0.f,  1.f,
                2.f,  3.f
            });
            Mtx<float, 2, 2> B({
                4.f,  5.f,
                6.f, -7.f
            });
            Mtx<float, 2, 2> C1({
                6.f,  -7.f,
               26.f, -11.f
            });
            Mtx<float, 2, 2> C2({
                10.f,   19.f,
               -14.f, -15.f
            });

            Assert::AreEqual(A * B == C1, true);
            Assert::AreEqual(B * A == C2, true);
        }

        TEST_METHOD(MO_1_5)
        {
            Mtx<float, 2, 3> A({
                1.f,   2.f, 3.f,
                4.f,  -5.f, 6.f
            });
            Mtx<float, 2, 2> B({
                7.f,   8.f,
                0.f,  -9.f
            });
            Mtx<float, 2, 3> C({
                 39.f, -26.f,  69.f,
                -36.f,  45.f, -54.f
            });


            // Works! - Does not compile :)
            // Assert::AreEqual(A * B == C, true);
            Assert::AreEqual(B * A == C, true);
        }

        TEST_METHOD(MO_1_6)
        {
            Mtx<float, 2, 3> A({
                1.f,   2.f, 3.f,
                4.f,  -5.f, 6.f
            });
            Mtx<float, 2, 2> B({
                7.f,   8.f,
                0.f,  -9.f
            });
            Mtx<float, 2, 3> C({
                 39.f, -26.f,  69.f,
                -36.f,  45.f, -54.f
            });

            Assert::AreEqual(t(B * A) == t(A) * t(B), true);
            Assert::AreEqual(t(B * A) == t(C), true);
            Assert::AreEqual(t(A) * t(B) == t(C), true);
        }

        TEST_METHOD(MO_1_7)
        {
            Mtx<float, 3, 3> A({
                 4.f,   2.f, 0.f,
                 2.f,   1.f, 0.f,
                -2.f,  -1.f, 1.f,
            });
            Mtx<float, 3, 3> B({
                 2.f,   3.f,  1.f,
                 2.f,  -2.f, -2.f,
                -1.f,   2.f,  1.f,
            });
            Mtx<float, 3, 3> C({
                 3.f,   1.f, -3.f,
                 0.f,   2.f,  6.f,
                -1.f,   2.f,  1.f,
            });
            Mtx<float, 3, 3> Y({
                12.f,   8.f,  0.f,
                 6.f,   4.f,  0.f,
                -7.f,  -2.f,  1.f,
            });

            Assert::AreEqual(A * B == A * C, true);
            Assert::AreEqual(A * B == Y, true);
            Assert::AreEqual(A * C == Y, true);
        }

        TEST_METHOD(MO_1_8)
        {
            Mtx<float, 3, 4> A({
                1.f,  2.f,  3.f,  4.f,
                0.f,  0.f,  5.f,  6.f,
                7.f,  8.f, -1.f, -2.f
            });
            Mtx<float, 1, 2> B({
                 1.f,   2.f
            });
            Mtx<float, 1, 2> C({
                 3.f,   4.f
            });
            Mtx<float, 2, 2> E({
                0.f,  0.f,
                7.f,  8.f
            });
            Mtx<float, 2, 2> F({
                 5.f,   6.f,
                -1.f,  -2.f
            });
            Mtx<float, 3, 3> G({
                1.f,  2.f,  3.f,
                0.f,  0.f,  5.f,
                7.f,  8.f, -1.f
            });
            Mtx<float, 3, 1> H({
                4.f,
                6.f,
               -2.f
            });

            Assert::AreEqual(A.part<0, 1, 0, 2>() == B, true);
            Assert::AreEqual(A.part<0, 1, 2, 4>() == C, true);
            Assert::AreEqual(A.part<1, 3, 0, 2>() == E, true);
            Assert::AreEqual(A.part<1, 3, 2, 4>() == F, true);
            Assert::AreEqual(A.part<0, 3, 0, 3>() == G, true);
            Assert::AreEqual(A.part<0, 3, 3, 4>() == H, true);
        }

        TEST_METHOD(MO_1_9)
        {
            Mtx<float, 2, 2> C({
                1.f,  2.f,
                3.f,  4.f,
            });
            Mtx<float, 2, 2> D({
                0.f,  0.f,
                0.f,  0.f,
            });
            Mtx<float, 2, 2> E({
                5.f,  6.f,
                7.f,  8.f,
            });
            Mtx<float, 2, 2> F({
               -1.f,  0.f,
                2.f,  1.f,
            });
            Mtx<float, 2, 2> G({
               -2.f, -3.f,
                1.f,  1.f,
            });
           Mtx<float, 4, 4> Q1 ({
                 3.f,  2.f,  0.f, -1.f,
                 5.f,  4.f, -2.f, -5.f,
                10.f,  8.f, 15.f, 13.f,
                14.f, 12.f, 37.f, 37.f
            });
            Mtx<float, 4, 4> Q2({
                 2.f,  2.f,  2.f,  3.f,
                 1.f,  3.f, -1.f, -1.f,
                 6.f,  6.f, -4.f, -4.f,
                 5.f,  7.f, -4.f, -4.f
            });

            Mtx<float, 4, 4> A = vcon(hcon(C, D), hcon(E, C));
            Mtx<float, 4, 4> B = vcon(hcon(F, G), hcon(F, E));

            Logger::WriteMessage((A * B).to_string("AB").c_str());
            Logger::WriteMessage((Q1).to_string("Q1").c_str());
            Logger::WriteMessage((A - B).to_string("A-B").c_str());
            Logger::WriteMessage((Q2).to_string("Q2").c_str());

            Assert::AreEqual(A * B == Q1, true);
            Assert::AreEqual(A - B == Q2, true);
        }
    };
}
