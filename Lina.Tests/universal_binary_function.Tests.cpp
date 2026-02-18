#include <CppUnitTest.h>
#include <exception>
#include <array>
#include "universal_binary_function.hpp"

using namespace Lina;
using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace LinaTests
{
	TEST_CLASS(universal_binary_function)
	{
    private:
        BEGIN_TEST_CLASS_ATTRIBUTE()
            TEST_CLASS_ATTRIBUTE(L"ubfun", L"Tests")
        END_TEST_CLASS_ATTRIBUTE()

    public:

        bool fz_eq(float x, float y, float e)
        {
            return abs(x - y) <= e;
        }

        TEST_METHOD(learn_and)
        {
            auto v = std::array<float,4>{.5f, .5f, .5f, .5f};
            float exp0 = 0.f;
            float exp1 = 0.f;
            float exp2 = 0.f;
            float exp3 = 1.f;

            for (int i = 10; i > 0; --i)
            {
                float res0 = ubfun(0.f, 0.f, v.data());
                learn_ubfun(exp0, res0, 0.f, 0.f, v.data());

                float res1 = ubfun(0.f, 1.f, v.data());
                learn_ubfun(exp1, res1, 0.f, 1.f, v.data());

                float res2 = ubfun(1.f, 0.f, v.data());
                learn_ubfun(exp2, res2, 1.f, 0.f, v.data());

                float res3 = ubfun(1.f, 1.f, v.data());
                learn_ubfun(exp3, res3, 1.f, 1.f, v.data());

                float score = 0.25f * (abs(exp0 - res0) + abs(exp1 - res1) + abs(exp2 - res2) + abs(exp3 - res3));
                std::wstring message = L"\nScore: " + std::to_wstring(score);
                Logger::WriteMessage(message.c_str());
            }

            float e = 0.0001f;
            Assert::IsTrue(fz_eq(ubfun(0.f, 0.f, v.data()), exp0, e));
            Assert::IsTrue(fz_eq(ubfun(0.f, 1.f, v.data()), exp1, e));
            Assert::IsTrue(fz_eq(ubfun(1.f, 0.f, v.data()), exp2, e));
            Assert::IsTrue(fz_eq(ubfun(1.f, 1.f, v.data()), exp3, e));
        }

        TEST_METHOD(learn_nand)
        {
            auto v = std::array<float,4>{.5f, .5f, .5f, .5f};
            float exp0 = 1.f;
            float exp1 = 1.f;
            float exp2 = 1.f;
            float exp3 = 0.f;

            for (int i = 10; i > 0; --i)
            {
                float res0 = ubfun(0.f, 0.f, v.data());
                learn_ubfun(exp0, res0, 0.f, 0.f, v.data());

                float res1 = ubfun(0.f, 1.f, v.data());
                learn_ubfun(exp1, res1, 0.f, 1.f, v.data());

                float res2 = ubfun(1.f, 0.f, v.data());
                learn_ubfun(exp2, res2, 1.f, 0.f, v.data());

                float res3 = ubfun(1.f, 1.f, v.data());
                learn_ubfun(exp3, res3, 1.f, 1.f, v.data());

                float score = 0.25f * (abs(exp0 - res0) + abs(exp1 - res1) + abs(exp2 - res2) + abs(exp3 - res3));
                std::wstring message = L"\nScore: " + std::to_wstring(score);
                Logger::WriteMessage(message.c_str());
            }

            float e = 0.0001f;
            Assert::IsTrue(fz_eq(ubfun(0.f, 0.f, v.data()), exp0, e));
            Assert::IsTrue(fz_eq(ubfun(0.f, 1.f, v.data()), exp1, e));
            Assert::IsTrue(fz_eq(ubfun(1.f, 0.f, v.data()), exp2, e));
            Assert::IsTrue(fz_eq(ubfun(1.f, 1.f, v.data()), exp3, e));
        }
    };
}
