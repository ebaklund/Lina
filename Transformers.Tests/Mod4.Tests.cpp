
#include "CppUnitTest.h"
#include <coroutine>
#include <generator>
#include <iostream>
#include <cstdlib>
#include <array>
#include <algorithm>
#include "Array.hpp"

using namespace Lina;
using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace TransformersTests
{
	TEST_CLASS(Mod4_Tests)
	{
        BEGIN_TEST_CLASS_ATTRIBUTE()
            TEST_CLASS_ATTRIBUTE(L"Mod4_Tests", L"Tests")
        END_TEST_CLASS_ATTRIBUTE()

    private:
        template<uint32_t Q>
        std::generator<uint32_t> rnd_mod(uint32_t seed)
        {
            srand(seed);

            while (true)
            {
                co_yield rand() % Q;
            }
        }

        template<uint32_t N>
        std::array<float,N> AsEmbedding(uint32_t v)
        {
            std::array<float,N> embedding { };
            std::ranges::fill(embedding, 0.0); 
            embedding[v] = 1.0;

            return embedding;
        }

	public:		
		TEST_METHOD(rnd_mod)
		{
            auto gen_mod_4 = rnd_mod<4>(99);
            auto it = gen_mod_4.begin();
            
            while(*(++it) != 0u);
            Assert::AreEqual(*it, 0u);
            
            while(*(++it) != 2u);
            Assert::AreEqual(*it, 2u);
            
            while(*(++it) != 1u);
            Assert::AreEqual(*it, 1u);
            
            while(*(++it) != 3u);
            Assert::AreEqual(*it, 3u);
		}

		TEST_METHOD(rnd_mod_emb)
		{
            const uint32_t N = 4;

            auto expected = to_string("", std::array<float, N> {1.f, 0.f, 0.f, 0.f});
            auto actual = to_string("", AsEmbedding<N>(0));
            Assert::AreEqual(expected, actual);

            expected = to_string("", std::array<float, N> {0.f, 1.f, 0.f, 0.f});
            actual = to_string("", AsEmbedding<N>(1));
            Assert::AreEqual(expected, actual);

            expected = to_string("", std::array<float, N> {0.f, 0.f, 1.f, 0.f});
            actual = to_string("", AsEmbedding<N>(2));
            Assert::AreEqual(expected, actual);

            expected = to_string("", std::array<float, N> {0.f, 0.f, 0.f, 1.f});
            actual = to_string("", AsEmbedding<N>(3));
            Assert::AreEqual(expected, actual);
		}
	};
}
