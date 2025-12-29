
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
            std::ranges::fill(emb, 0.f); 
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
            const uint32_t Dim = 4;
            std::array<float,Dim> embedding;

            embed_value<Dim>(embedding, 0u);
            auto actual = to_string("",embedding);
            auto expected = to_string("", std::array<float, Dim> {1.f, 0.f, 0.f, 0.f});
            Assert::AreEqual(expected, actual);

            embed_value<Dim>(embedding, 1u);
            actual = to_string("",embedding);
            expected = to_string("", std::array<float, Dim> {0.f, 1.f, 0.f, 0.f});
            Assert::AreEqual(expected, actual);

            embed_value<Dim>(embedding, 2u);
            actual = to_string("",embedding); 
            expected = to_string("", std::array<float, Dim> {0.f, 0.f, 1.f, 0.f});
            Assert::AreEqual(expected, actual);

            embed_value<Dim>(embedding, 3u);
            actual = to_string("",embedding);
            expected = to_string("", std::array<float, Dim> {0.f, 0.f, 0.f, 1.f});
            Assert::AreEqual(expected, actual);
		}

        TEST_METHOD(learn_mod4)
		{
            const float is_expected = 1.f;
            const uint32_t divisor  = 4u;
            const uint32_t Dim      = 64u;

            Transformer<float,Dim,Dim> trf;
            std::array<float,Dim> dividend_token;
            std::array<float,Dim> divisor_token;
            std::array<float,Dim> requester_token;
            std::array<float,Dim> expected_token;

            embed_value<Dim>(divisor_token, divisor);
            std::ranges::fill(requester_token, 1.f);

            int i = 10;

            for (auto dividend : gen_rnd<Dim>(2))
            {
                if ((i--) == 0)
                    break;
             
                auto expected_remainder = dividend % divisor; 
                embed_value<Dim>(dividend_token, dividend);
                embed_value<Dim>(expected_token, expected_remainder);

                trf.get_next(dividend_token);
                trf.get_next(divisor_token);
                auto predicted_token = trf.get_next(requester_token);
                float score = 1.f - nml1_dist<float,Dim>(expected_token, predicted_token);
                trf.learn_from(score);

                std::wstring message = L"Score: " + std::to_wstring(score);
                Logger::WriteMessage(message.c_str());
            }

            Assert::AreEqual(true, false);
        }
	};
}
