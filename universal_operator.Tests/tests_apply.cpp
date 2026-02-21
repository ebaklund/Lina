
#include <CppUnitTest.h>
#include <cstdlib>
#include <array>
#include <algorithm>
#include <UniversalOperator/universal_operator.hpp>

using namespace Lina;
using namespace Microsoft::VisualStudio::CppUnitTestFramework;


namespace UniversalOperatorTests
{
	TEST_CLASS(UniversalOperator_Tests)
	{
        BEGIN_TEST_CLASS_ATTRIBUTE()
            TEST_CLASS_ATTRIBUTE(L"UniversalOperator", L"apply")
        END_TEST_CLASS_ATTRIBUTE()

    private:
        bool fz_eq(float x, float y)
        {
            static const float e = 0.0001f;
            return abs(x - y) <= e;
        }

        std::array<float,4> _and { 1.f, 0.f, 0.f, 0.f };
        std::array<float,4> _nand { 0.f, 1.f, 1.f, 1.f };
        std::array<float,4> _or { 1.f, 1.f, 1.f, 0.f };
        std::array<float,4> _nor { 0.f, 0.f, 0.f, 1.f };
        std::array<float,4> _xor { 0.f, 1.f, 1.f, 0.f }; // !=
        std::array<float,4> _nxor { 1.f, 0.f, 0.f, 1.f }; // ==


	public:
		TEST_METHOD(Apply_1x1x1_and)
		{
            UniversalOperator<float, 1, 1, 1> uop(_and);
            std::array<float, 1> a;
            std::array<float, 1> b;
            std::array<float, 1> c;

            a[0] = 0.f;
            b[0] = 0.f;
            uop.apply(a, b, c);
            Assert::IsTrue (fz_eq (c[0], 0.f));

            a[0] = 0.f;
            b[0] = 1.f;
            uop.apply(a, b, c);
            Assert::IsTrue (fz_eq (c[0], 0.f));

            a[0] = 1.f;
            b[0] = 0.f;
            uop.apply(a, b, c);
            Assert::IsTrue (fz_eq (c[0], 0.f));

            a[0] = 1.f;
            b[0] = 1.f;
            uop.apply(a, b, c);
            Assert::IsTrue (fz_eq (c[0], 1.f));
		}

        TEST_METHOD(Apply_1x1x1_xor)
		{
            UniversalOperator<float, 1, 1, 1> uop(_xor);
            std::array<float, 1> a;
            std::array<float, 1> b;
            std::array<float, 1> c;

            a[0] = 0.f;
            b[0] = 0.f;
            uop.apply(a, b, c);
            Assert::IsTrue (fz_eq (c[0], 0.f));

            a[0] = 0.f;
            b[0] = 1.f;
            uop.apply(a, b, c);
            Assert::IsTrue (fz_eq (c[0], 1.f));

            a[0] = 1.f;
            b[0] = 0.f;
            uop.apply(a, b, c);
            Assert::IsTrue (fz_eq (c[0], 1.f));

            a[0] = 1.f;
            b[0] = 1.f;
            uop.apply(a, b, c);
            Assert::IsTrue (fz_eq (c[0], 0.f));
		}
		TEST_METHOD(Apply_1x2x1_and_and)
		{
            static const uint32_t FSIZE = 4*1*2*1;
            std::array<float, FSIZE> fluents;

            for (uint32_t i = 0; i < FSIZE; ++i) {
                fluents[i] = _and[i%4];
            }

            UniversalOperator<float, 1, 2, 1> uop(fluents);

            std::array<float, 1> c;
            std::array<float, 16> expected = {
                0.f, 0.f, 0.f, .5f,
                0.f, 0.f, 0.f, .5f,
                0.f, 0.f, 0.f, .5f,
                .5f, .5f, .5f, 1.f
            };

            for (uint32_t i = 0; i < 16; ++i) {
                std::array<float, 2> a = { float((i/1)%2), float((i/4)%2) };
                std::array<float, 2> b = { float((i/2)%2), float((i/8)%2) };
                uop.apply(a, b, c);

                if (! fz_eq (c[0], expected[i])) {
                    float cv = c[0];
                    float ev = expected[i];
                    Assert::IsTrue (fz_eq (cv, ev));
                }

                Assert::IsTrue (fz_eq (c[0], expected[i]));
            }
		}
		TEST_METHOD(Apply_1x2x1_and_or)
		{
            static const uint32_t FSIZE = 4*1*2*1;
            std::array<float, FSIZE> fluents;

            for (uint32_t i = 0; i < FSIZE/2; ++i) {
                fluents[i] = _and[i%4];
            }
            for (uint32_t i = FSIZE/2; i < FSIZE; ++i) {
                fluents[i] = _or[i%4];
            }

            UniversalOperator<float, 1, 2, 1> uop(fluents);

            std::array<float, 1> c;
            std::array<float, 16> expected = {
                0.f, 0.f, 0.f, .5f,
                .5f, .5f, .5f, 1.f,
                .5f, .5f, .5f, 1.f,
                .5f, .5f, .5f, 1.f,
            };

            for (uint32_t i = 0; i < 16; ++i) {
                std::array<float, 2> a = { float((i/1)%2), float((i/4)%2) };
                std::array<float, 2> b = { float((i/2)%2), float((i/8)%2) };
                uop.apply(a, b, c);

                if (! fz_eq (c[0], expected[i])) {
                    float cv = c[0];
                    float ev = expected[i];
                    Assert::IsTrue (fz_eq (cv, ev));
                }

                Assert::IsTrue (fz_eq (c[0], expected[i]));
            }
		}
		TEST_METHOD(Apply_1x2x1_or_and)
		{
            static const uint32_t FSIZE = 4*1*2*1;
            std::array<float, FSIZE> fluents;

            for (uint32_t i = 0; i < FSIZE/2; ++i) {
                fluents[i] = _or[i%4];
            }
            for (uint32_t i = FSIZE/2; i < FSIZE; ++i) {
                fluents[i] = _and[i%4];
            }

            UniversalOperator<float, 1, 2, 1> uop(fluents);

            std::array<float, 1> c;
            std::array<float, 16> expected = {
                0.f, .5f, .5f, .5f,
                0.f, .5f, .5f, .5f,
                0.f, .5f, .5f, .5f,
                .5f, 1.f, 1.f, 1.f,
            };

            for (uint32_t i = 0; i < 16; ++i) {
                std::array<float, 2> a = { float((i/1)%2), float((i/4)%2) };
                std::array<float, 2> b = { float((i/2)%2), float((i/8)%2) };
                uop.apply(a, b, c);

                if (! fz_eq (c[0], expected[i])) {
                    float cv = c[0];
                    float ev = expected[i];
                    Assert::IsTrue (fz_eq (cv, ev));
                }

                Assert::IsTrue (fz_eq (c[0], expected[i]));
            }
		}
		TEST_METHOD(Apply_1x2x1_or_or)
		{
            static const uint32_t FSIZE = 4*1*2*1;
            std::array<float, FSIZE> fluents;

            for (uint32_t i = 0; i < FSIZE/2; ++i) {
                fluents[i] = _or[i%4];
            }
            for (uint32_t i = FSIZE/2; i < FSIZE; ++i) {
                fluents[i] = _or[i%4];
            }

            UniversalOperator<float, 1, 2, 1> uop(fluents);

            std::array<float, 1> c;
            std::array<float, 16> expected = {
                0.f, .5f, .5f, .5f,
                .5f, 1.f, 1.f, 1.f,
                .5f, 1.f, 1.f, 1.f,
                .5f, 1.f, 1.f, 1.f,
            };

            for (uint32_t i = 0; i < 16; ++i) {
                std::array<float, 2> a = { float((i/1)%2), float((i/4)%2) };
                std::array<float, 2> b = { float((i/2)%2), float((i/8)%2) };
                uop.apply(a, b, c);

                if (! fz_eq (c[0], expected[i])) {
                    float cv = c[0];
                    float ev = expected[i];
                    Assert::IsTrue (fz_eq (cv, ev));
                }

                Assert::IsTrue (fz_eq (c[0], expected[i]));
            }
		}
    };
}

