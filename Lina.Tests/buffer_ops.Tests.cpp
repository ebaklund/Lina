#include <CppUnitTest.h>
#include <exception>
#include <array>
#include "buffer_ops.hpp"

using namespace Lina;
using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace LinaTests
{
	TEST_CLASS(buffer_ops)
	{
    private:
        BEGIN_TEST_CLASS_ATTRIBUTE()
            TEST_CLASS_ATTRIBUTE(L"buffer_ops", L"Tests")
        END_TEST_CLASS_ATTRIBUTE()

    public:
        TEST_METHOD(nml1_dist)
        {
            const uint32_t Dim = 4u;
            float dist;

            dist = Lina::nml1_dist<float,Dim>(
                std::array<float,Dim>{0.f, 0.f, 0.f, 0.f}.data(),
                std::array<float,Dim>{0.f, 0.f, 0.f, 0.f}.data()
            );
            Assert::AreEqual(0.f, dist);

            dist = Lina::nml1_dist<float,Dim>(
                std::array<float,Dim>{0.f, 0.f, 0.f, 1.f}.data(),
                std::array<float,Dim>{0.f, 0.f, 0.f, 0.f}.data()
            );
            Assert::AreEqual(0.25f, dist);

            dist = Lina::nml1_dist<float,Dim>(
                std::array<float,Dim>{0.f, 0.f, 0.f, 0.f}.data(),
                std::array<float,Dim>{0.f, 0.f, 0.f, 1.f}.data()
            );
            Assert::AreEqual(0.25f, dist);

            dist = Lina::nml1_dist<float,Dim>(
                std::array<float,Dim>{1.f, 0.f, 0.f, 0.f}.data(),
                std::array<float,Dim>{0.f, 0.f, 0.f, 0.f}.data()
            );
            Assert::AreEqual(0.25f, dist);

            dist = Lina::nml1_dist<float,Dim>(
                std::array<float,Dim>{0.f, 0.f, 0.f, 0.f}.data(),
                std::array<float,Dim>{1.f, 0.f, 0.f, 0.f}.data()
            );
            Assert::AreEqual(0.25f, dist);

            dist = Lina::nml1_dist<float,Dim>(
                std::array<float,Dim>{1.f, 1.f, 1.f, 1.f}.data(),
                std::array<float,Dim>{0.f, 0.f, 0.f, 0.f}.data()
            );
            Assert::AreEqual(1.f, dist);

            dist = Lina::nml1_dist<float,Dim>(
                std::array<float,Dim>{0.f, 0.f, 0.f, 0.f}.data(),
                std::array<float,Dim>{1.f, 1.f, 1.f, 1.f}.data()
            );
            Assert::AreEqual(1.f, dist);

            dist = Lina::nml1_dist<float,Dim>(
                std::array<float,Dim>{0.f, 0.f, 0.f, 0.f}.data(),
                std::array<float,Dim>{1.f, 1.f, 1.1f, 1.f}.data()
            );
            Assert::AreNotEqual(1.f, dist);
        }
    };
}
