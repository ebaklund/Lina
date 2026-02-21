
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

        void set_breakpoint_here() {};

        std::array<float,4> _default { .5f, .5f, .5f, .5f };
        std::array<float,4> _ramp { .8f, .4f, .2f, .1f };
        std::array<float,4> _and { 1.f, 0.f, 0.f, 0.f };
        std::array<float,4> _nand { 0.f, 1.f, 1.f, 1.f };
        std::array<float,4> _or { 1.f, 1.f, 1.f, 0.f };
        std::array<float,4> _nor { 0.f, 0.f, 0.f, 1.f };
        std::array<float,4> _xor { 0.f, 1.f, 1.f, 0.f }; // !=
        std::array<float,4> _nxor { 1.f, 0.f, 0.f, 1.f }; // ==

        template<typename T>
        void test_apply_1x1x1(std::array<T,4> const& expected, std::array<float,4> f1) {
            std::array<float, 4> fluents;

            for (uint32_t i = 0; i < 4; ++i) {
                fluents[i] = f1[i];
            }

            UniversalOperator<float, 1, 1, 1> uop(fluents); // SUT

            for (uint32_t i = 0; i < 4; ++i) {
                std::array<float, 1> a = { float(i/2) };
                std::array<float, 1> b = { float(i%2) };
                std::array<float, 1> c;
    
                uop.apply(a, b, c); // SUT Test
                bool debug = ! fz_eq (c[0], expected[i]);

                if (debug) {                     
                    float cv = c[0];
                    float ev = expected[i];
                    set_breakpoint_here();
                }

                Assert::IsTrue (fz_eq (c[0], expected[i]));
            }
        }

        template<typename T, uint32_t R1, uint32_t C2>
        void test_apply_d2(std::array<T,16> const& expected, std::array<float,4> f1, std::array<float,4> f2) {
            static const uint32_t D = 2;
            static const uint32_t FSIZE = 4*1*D*1;
            std::array<float, FSIZE> fluents;

            for (uint32_t i = 0; i < FSIZE/2; ++i) {
                fluents[i] = f1[i%4];
            }
            for (uint32_t i = FSIZE/2; i < FSIZE; ++i) {
                fluents[i] = f2[i%4];
            }

            UniversalOperator<float, 1, D, 1> uop(fluents); // SUT

            for (uint32_t i = 0; i < 16; ++i) {
                std::array<float, 2> a = { float((i/2)%2), float((i/8)%2) };
                std::array<float, 2> b = { float((i/1)%2), float((i/4)%2) };
                std::array<float, 1> c;
    
                uop.apply(a, b, c); // SUT Test
                bool debug = ! fz_eq (c[0], expected[i]);

                if (debug) {                     
                    float cv = c[0];
                    float ev = expected[i];
                    set_breakpoint_here();
                }

                Assert::IsTrue (fz_eq (c[0], expected[i]));
            }
        }

	public:
		TEST_METHOD(Apply_1x1x1_default)
		{
            std::array<float, 4> expected = {
                .5f, .5f, .5f, .5f,
            };

            test_apply_1x1x1<float>(expected, _default);
		}

        TEST_METHOD(Apply_1x1x1_ramp)
		{
            std::array<float, 4> expected = {
                .1f, .2f, .4f, .8f,
            };

            test_apply_1x1x1<float>(expected, _ramp);
		}
        
        TEST_METHOD(Apply_1x1x1_and)
		{
            std::array<float, 4> expected = {
                0.f, 0.f, 0.f, 1.f,
            };

            test_apply_1x1x1<float>(expected, _and);
		}

        TEST_METHOD(Apply_1x1x1_xor)
		{
            std::array<float, 4> expected = {
                0.f, 1.f, 1.f, 0.f,
            };

            test_apply_1x1x1<float>(expected, _xor);
		}

		TEST_METHOD(Apply_1x2x1_default_default)
		{
            std::array<float, 16> expected = {
                .5f, .5f, .5f, .5f,
                .5f, .5f, .5f, .5f,
                .5f, .5f, .5f, .5f,
                .5f, .5f, .5f, .5f,
            };

            test_apply_d2<float, 1, 1>(expected, _default, _default);
		}

		TEST_METHOD(Apply_1x2x1_ramp_ramp)
		{
            std::array<float, 16> expected = {
                .1f, .15f, .25f, .45f,
                .15f,.20f, .30f, .50f,
                .25, .30f, .40f, .60f,
                .45f,.50f, .60f, .80f,
            };

            test_apply_d2<float, 1, 1>(expected, _ramp, _ramp);
		}

		TEST_METHOD(Apply_1x2x1_and_and)
		{
            std::array<float, 16> expected = {
                0.f, 0.f, 0.f, .5f,
                0.f, 0.f, 0.f, .5f,
                0.f, 0.f, 0.f, .5f,
                .5f, .5f, .5f, 1.f
            };

            test_apply_d2<float, 1, 1>(expected, _and, _and);
		}

		TEST_METHOD(Apply_1x2x1_and_or)
		{
            std::array<float, 16> expected = {
                0.f, 0.f, 0.f, .5f,
                .5f, .5f, .5f, 1.f,
                .5f, .5f, .5f, 1.f,
                .5f, .5f, .5f, 1.f,
            };

            test_apply_d2<float, 1, 1>(expected, _and, _or);
		}

		TEST_METHOD(Apply_1x2x1_or_and)
		{
            std::array<float, 16> expected = {
                0.f, .5f, .5f, .5f,
                0.f, .5f, .5f, .5f,
                0.f, .5f, .5f, .5f,
                .5f, 1.f, 1.f, 1.f,
            };

            test_apply_d2<float, 1, 1>(expected, _or, _and);
        }

		TEST_METHOD(Apply_1x2x1_or_or)
		{
            std::array<float, 16> expected = {
                0.f, .5f, .5f, .5f,
                .5f, 1.f, 1.f, 1.f,
                .5f, 1.f, 1.f, 1.f,
                .5f, 1.f, 1.f, 1.f,
            };

            test_apply_d2<float, 1, 1>(expected, _or, _or);
		}
    };
}

