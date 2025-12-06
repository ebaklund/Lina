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
        TEST_METHOD(Constructor)
        {
            Rational a;
            Rational b(0, 0);
            Rational c(b);
            Rational d = c;

            auto r = Rational::from;
            Rational e = r(1, 1);
        }
        TEST_METHOD(eq)
        {
            auto r = Rational::from;
            Assert::AreEqual(r(0, 1), Rational());
            Assert::AreEqual(r(0, 1), Rational(0));
            Assert::AreEqual(r(0, 1), Rational(0, 1));
            Assert::AreEqual(r(1, 1), Rational(1));
            Assert::AreEqual(r(1, 1), Rational(1, 1));
        }
    };
}
