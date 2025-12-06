#include <CppUnitTest.h>
#include <exception>
#include "rational.hpp"

namespace Microsoft
{
    namespace VisualStudio
    {
        namespace CppUnitTestFramework
        {
            template<> static std::wstring ToString<Lina::Rational>(const class Lina::Rational& r)
            {
                return r.to_wstring(); 
            }
        }
    }
}

using namespace Lina;
using namespace Microsoft::VisualStudio::CppUnitTestFramework;


namespace LinaTests
{
	TEST_CLASS(RationalTests)
	{
        BEGIN_TEST_CLASS_ATTRIBUTE()
            TEST_CLASS_ATTRIBUTE(L"Rational", L"Tests")
        END_TEST_CLASS_ATTRIBUTE()

    public:
        TEST_METHOD(t00_Constructor)
        {
            Rational a;
            Rational b(0, 0);
            Rational c(b);
            Rational d = c;

            auto r = Rational::from;
            Rational e = r(1, 1);
        }
        TEST_METHOD(t01_eq)
        {
            auto r = Rational::from;
            Assert::AreEqual(r(0, 1), Rational());
            Assert::AreEqual(r(0, 1), Rational(0));
            Assert::AreEqual(r(0, 1), Rational(0, 1));
            Assert::AreEqual(r(1, 1), Rational(1));
            Assert::AreEqual(r(1, 1), Rational(1, 1));
        }
        TEST_METHOD(t02_add)
        {
            auto r = Rational::from;
            Assert::AreEqual(r(0, -1) + r(0, -1), r(0, 1));
            Assert::AreEqual(r(0, -1) + r(1, -1), r(-1, 1));
            Assert::AreEqual(r(1, -1) + r(0, -1), r(-1, 1));
            Assert::AreEqual(r(1, -1) + r(1, -1), r(-2, 1));

            Assert::AreEqual(r(0, 1) + r(0, 1), r(0, 1));
            Assert::AreEqual(r(0, 1) + r(1, 1), r(1, 1));
            Assert::AreEqual(r(1, 1) + r(0, 1), r(1, 1));
            Assert::AreEqual(r(1, 1) + r(1, 1), r(2, 1));

            Assert::AreEqual(r(0, 2) + r(0, 2), r(0, 1));
            Assert::AreEqual(r(0, 2) + r(1, 2), r(1, 2));
            Assert::AreEqual(r(1, 2) + r(0, 2), r(1, 2));
            Assert::AreEqual(r(1, 2) + r(1, 2), r(1, 1));
        }
        TEST_METHOD(t03_sub)
        {
            auto r = Rational::from;
            Assert::AreEqual(r(0, 1), r(0, -1) - r(0, -1));
            Assert::AreEqual(r(1, 1), r(0, -1) - r(1, -1));
            Assert::AreEqual(r(-1, 1), r(1, -1) - r(0, -1));
            Assert::AreEqual(r(0, 1), r(1, -1) - r(1, -1));

            Assert::AreEqual(r(0, 1), r(0, 1) - r(0, 1));
            Assert::AreEqual(r(-1, 1), r(0, 1) - r(1, 1));
            Assert::AreEqual(r(1, 1), r(1, 1) - r(0, 1));
            Assert::AreEqual(r(0, 1), r(1, 1) - r(1, 1));

            Assert::AreEqual(r(0, 1), r(0, 2) - r(0, 2));
            Assert::AreEqual(r(-1, 2), r(0, 2) - r(1, 2));
            Assert::AreEqual(r(1, 2), r(1, 2) - r(0, 2));
            Assert::AreEqual(r(0, 1), r(1, 2) - r(1, 2));
        }
        TEST_METHOD(t04_mul)
        {
            auto r = Rational::from;
            Assert::AreEqual(r(0, 1), r(0, -1) * r(0, -1));
            Assert::AreEqual(r(0, 1), r(0, -1) * r(1, -1));
            Assert::AreEqual(r(0, 1), r(1, -1) * r(0, -1));
            Assert::AreEqual(r(1, 1), r(1, -1) * r(1, -1));

            Assert::AreEqual(r(0, 1), r(0, 1) * r(0, 1));
            Assert::AreEqual(r(0, 1), r(0, 1) * r(1, 1));
            Assert::AreEqual(r(0, 1), r(1, 1) * r(0, 1));
            Assert::AreEqual(r(1, 1), r(1, 1) * r(1, 1));

            Assert::AreEqual(r(0, 1), r(0, 2) * r(0, 2));
            Assert::AreEqual(r(0, 2), r(0, 2) * r(1, 2));
            Assert::AreEqual(r(0, 2), r(1, 2) * r(0, 2));
            Assert::AreEqual(r(1, 4), r(1, 2) * r(1, 2));
        }
        TEST_METHOD(t05_div)
        {
            auto r = Rational::from;
            Assert::AreEqual(r(0, 1), r(0, -1) / r(1, -1));
            Assert::AreEqual(r(1, 1), r(1, -1) / r(1, -1));

            Assert::AreEqual(r(0, 1), r(0, 1) / r(1, -1));
            Assert::AreEqual(r(-1, 1), r(1, 1) / r(1, -1));

            Assert::AreEqual(r(0, 1), r(0, 1) / r(1, 1));
            Assert::AreEqual(r(1, 1), r(1, 1) / r(1, 1));

            Assert::AreEqual(r(0, 2), r(0, 2) / r(1, 2));
            Assert::AreEqual(r(1, 1), r(1, 2) / r(1, 2));
        }
    };
}
