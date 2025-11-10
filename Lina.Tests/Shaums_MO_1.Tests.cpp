
#include "CppUnitTest.h"
#include "..\Lina\Lina.hpp"

using namespace Lina;
using namespace Microsoft::VisualStudio::CppUnitTestFramework;


namespace LinaTests
{
	TEST_CLASS(LinaTests)
	{
	public:
		
		TEST_METHOD(MO_1_1)
		{
            Mtx<float, 3, 1> A ({ 2.f,  3.f,  4.f }); 
            Mtx<float, 3, 1> B ({ 5.f,  6.f, -7.f });
            Mtx<float, 1, 3> C ({ 7.f, -8.f, -9.f });
            
            Assert::AreEqual(dot(A, B), 0.f);
            Assert::AreEqual(dot(B, *t(C)), 50.f);
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

            Assert::AreEqual(*(A + B) == C, true);
            Assert::AreEqual(*(B + A) == C, true);
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

            Assert::AreEqual(*(*(3.0f * A) - *(0.5f * B)) == C, true);
        }
    };
}
