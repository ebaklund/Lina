
#include "CppUnitTest.h"
#include <coroutine>
#include <generator>
#include <iostream>
#include <cstdlib>
#include <array>
#include <algorithm>
#include "array_ops.hpp"
#include "buffer_ops.hpp"
#include "Transformer.hpp"

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
        std::generator<uint32_t> gen_rnd(uint32_t seed)
        {
            srand(seed);

            while (true)
                co_yield rand();
        }

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

        TEST_METHOD(learn_mod4)
		{
            const auto is_expected = 1.f;
            const auto modulo = 4u;
            const auto N = modulo + 1;
            auto trf = Transformer<float,N,N>();
            const auto  modulo_emb = AsEmbedding<N>(modulo);
            int i = 10;

            for (auto dividend : gen_rnd(99))
            {
                auto expected = dividend % modulo; // Remainder

                if ((i--) == 0)
                    break;

                auto  dividend_emb = AsEmbedding<N>(dividend);
                auto expected_emb = AsEmbedding<N>(expected);
                expected_emb[N - 1] = is_expected;

                trf.get_next(dividend_emb);
                auto prediction_emb = trf.get_next(modulo_emb);
                auto score = dot<float,N>(expected_emb, prediction_emb);
                trf.learn_from(score);
            }
        }
	};
}
