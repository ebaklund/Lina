
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
	};
}
