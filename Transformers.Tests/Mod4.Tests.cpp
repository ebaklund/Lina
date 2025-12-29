
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
        template<uint32_t N>
        std::generator<uint32_t> gen_rnd(uint32_t seed)
        {
            srand(seed);

            while (true)
                co_yield rand() % N;
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
        void embed_value(std::array<float,N>& emb, uint32_t v)
        {
            std::ranges::fill(emb, 0.0); 
            emb[v] = 1.0;
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
            std::array<float,N> embedding;

            embed_value<N>(embedding, 0u);
            auto actual = to_string("",embedding);
            auto expected = to_string("", std::array<float, N> {1.f, 0.f, 0.f, 0.f});
            Assert::AreEqual(expected, actual);

            embed_value<N>(embedding, 1u);
            actual = to_string("",embedding);
            expected = to_string("", std::array<float, N> {0.f, 1.f, 0.f, 0.f});
            Assert::AreEqual(expected, actual);

            embed_value<N>(embedding, 2u);
            actual = to_string("",embedding); 
            expected = to_string("", std::array<float, N> {0.f, 0.f, 1.f, 0.f});
            Assert::AreEqual(expected, actual);

            embed_value<N>(embedding, 3u);
            actual = to_string("",embedding);
            expected = to_string("", std::array<float, N> {0.f, 0.f, 0.f, 1.f});
            Assert::AreEqual(expected, actual);
		}

        TEST_METHOD(learn_mod4)
		{
            const float is_expected = 1.f;
            const uint32_t divisor  = 4u;
            const uint32_t N        = 64u;

            Transformer<float,N,N> trf;
            std::array<float,N> dividend_token;
            std::array<float,N> divisor_token;
            std::array<float,N> requester_token;
            std::array<float,N> expected_token;

            embed_value<N>(divisor_token, divisor);
            std::ranges::fill(requester_token, 1.f);

            int i = 10;

            for (auto dividend : gen_rnd<N>(2))
            {
                if ((i--) == 0)
                    break;
             
                auto expected_remainder = dividend % divisor; 
                embed_value<N>(dividend_token, dividend);
                embed_value<N>(expected_token, expected_remainder);

                trf.get_next(dividend_token);
                trf.get_next(divisor_token);
                auto predicted_token = trf.get_next(requester_token);
                auto score = sin<float,N>(expected_token, predicted_token);
                trf.learn_from(score);

                std::wstring message = L"Score: " + std::to_wstring(score);
                Logger::WriteMessage(message.c_str());
            }

            Assert::AreEqual(true, false);
        }
	};
}
